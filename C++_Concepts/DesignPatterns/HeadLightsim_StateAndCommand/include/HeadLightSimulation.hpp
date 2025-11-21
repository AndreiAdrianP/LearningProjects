#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
// --- Forward Declarations ---
class HeadlightContext;
class IHeadlightState;
// --- IHeadlightState (Abstract State Base) ---
class IHeadlightState {
public:
    virtual ~IHeadlightState() = default;
    virtual void handle_event(HeadlightContext& context, const std::string& event) = 0;
    virtual void entry_action() const = 0;
};

// --- HeadlightContext (Context) ---
class HeadlightContext {
private:
    std::unique_ptr<IHeadlightState> current_state_;
    bool auto_mode_active_ = false;

public:
    HeadlightContext(); 

    void transition_to(std::unique_ptr<IHeadlightState> new_state) {
        if (new_state) {
            current_state_ = std::move(new_state);
            current_state_->entry_action();
        }
    }

    void process_event(const std::string& event) {
        if (current_state_) {
            std::cout << "Context received input: " << event << std::endl;
            current_state_->handle_event(*this, event);
        }
    }
    
    // State machine helpers
    bool is_auto_mode() const { return auto_mode_active_; }
    void set_auto_mode(bool active) { 
        auto_mode_active_ = active;
        std::cout << "--> Auto Mode " << (active ? "ENABLED" : "DISABLED") << std::endl;
    }
};


class OffState : public IHeadlightState {
public:
    void entry_action() const override {
        std::cout << "--> System State: HEADLIGHTS OFF" << std::endl;
    }

    void handle_event(HeadlightContext& context, const std::string& event) override;
};

class LowBeamState : public IHeadlightState {
public:
    void entry_action() const override {
        std::cout << "--> System State: LOW BEAMS ON" << std::endl;
    }
    
    void handle_event(HeadlightContext& context, const std::string& event) override;
};

class HighBeamState : public IHeadlightState {
public:
    void entry_action() const override {
        std::cout << "--> System State: HIGH BEAMS ON" << std::endl;
    }

    void handle_event(HeadlightContext& context, const std::string& event) override;
};





