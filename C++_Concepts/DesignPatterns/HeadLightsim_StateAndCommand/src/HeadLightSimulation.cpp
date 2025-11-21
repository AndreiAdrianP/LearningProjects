#include "HeadLightSimulation.hpp"




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