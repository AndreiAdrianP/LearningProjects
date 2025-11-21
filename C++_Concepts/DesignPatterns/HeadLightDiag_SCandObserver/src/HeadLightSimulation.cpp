#include "HeadLightSimulation.hpp"
#include <algorithm> 
#include <stdexcept>

void HeadlightContext::attach(IHeadlightObserver* observer) {
    // Adds the observer's pointer to the list
    observers_.push_back(observer); 
};

void HeadlightContext::detach(IHeadlightObserver* observer) {
    // Finds and removes the observer's pointer from the list
    observers_.erase(
        std::remove(observers_.begin(), observers_.end(), observer),
        observers_.end()
    );
}
void HeadlightContext::notify() {
     std::string current_state_name = "UNKNOWN";

    // 1. Determine the current state name (used for the update data)
    // Uses dynamic_cast to figure out which concrete state we are in.
    if (current_state_) {
        if (dynamic_cast<OffState*>(current_state_.get())) {
            current_state_name = "OFF";
        } else if (dynamic_cast<LowBeamState*>(current_state_.get())) {
            current_state_name = "LOW_BEAM";
        } else if (dynamic_cast<HighBeamState*>(current_state_.get())) {
            current_state_name = "HIGH_BEAM";
        }
    }

    bool auto_status = auto_mode_active_;

    // 2. Loop and call update() on every single subscribed service
    for (IHeadlightObserver* observer : observers_) {
        observer->update(current_state_name, auto_status);
    }
}


void OffState::handle_event(HeadlightContext& context, const std::string& event) {
    if (event == "switch_to_low") {
        context.transition_to(std::make_unique<LowBeamState>());
    } else if (event == "toggle_auto") {
        context.set_auto_mode(!context.is_auto_mode());
    } else {
        std::cout << "[OffState] Ignored event: " << event << std::endl;
    }
}

void LowBeamState::handle_event(HeadlightContext& context, const std::string& event) {
    if (event == "switch_to_off") {
        context.transition_to(std::make_unique<OffState>());
    } else if (event == "switch_to_high") {
        context.transition_to(std::make_unique<HighBeamState>());
    } else if (event == "toggle_auto") {
        context.set_auto_mode(!context.is_auto_mode());
    } else {
        std::cout << "[LowBeamState] Ignored event: " << event << std::endl;
    }
}

void HighBeamState::handle_event(HeadlightContext& context, const std::string& event) {
    if (event == "switch_to_low") {
        context.transition_to(std::make_unique<LowBeamState>());
    } else if (event == "switch_to_off") {
        context.transition_to(std::make_unique<OffState>());
    } else {
        std::cout << "[HighBeamState] Ignored event: " << event << std::endl;
    }
}

// Set initial state after concrete states are defined
HeadlightContext::HeadlightContext() {
    std::cout << "--- Headlight ECU Initialized ---" << std::endl;
    transition_to(std::make_unique<OffState>()); // Start in OffState
}

 void HeadlightContext::set_auto_mode(bool active) { 
        auto_mode_active_ = active;
        std::cout << "--> Auto Mode " << (active ? "ENABLED" : "DISABLED") << std::endl;
        notify();
    }
void HeadlightContext::transition_to(std::unique_ptr<IHeadlightState> new_state) {
        if (new_state) {
            current_state_ = std::move(new_state);
            current_state_->entry_action();
             notify();
        }
    }

void HeadlightContext::process_event(const std::string& event) {
    if (current_state_) {
        std::cout << "Context received input: " << event << std::endl;
        current_state_->handle_event(*this, event);
    }
}