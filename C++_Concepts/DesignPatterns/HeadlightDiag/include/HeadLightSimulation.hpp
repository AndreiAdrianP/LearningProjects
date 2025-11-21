#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
// --- Forward Declarations ---
class HeadlightContext;
class IHeadlightState;
class IHeadlightObserver;
// --- IHeadlightState (Abstract State Base) ---
class IHeadlightState {
public:
    virtual ~IHeadlightState()=default;
    virtual void handle_event(HeadlightContext& context, const std::string& event) = 0;
    virtual void entry_action() const = 0;
};

// --- HeadlightContext (Context) ---
class HeadlightContext {
private:
    std::unique_ptr<IHeadlightState> current_state_;
    bool auto_mode_active_ = false;
    std::vector<IHeadlightObserver*> observers_;
public:
    HeadlightContext(); 

    void transition_to(std::unique_ptr<IHeadlightState> new_state);

    void process_event(const std::string& event);
    
    // State machine helpers
    bool is_auto_mode() const { return auto_mode_active_; }
    void set_auto_mode(bool active);
    void detach(IHeadlightObserver* observer);
    void attach(IHeadlightObserver* observer);
    void notify();

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

//abstract base class for diag
class IHeadlightObserver{
    public:
        virtual ~IHeadlightObserver() = default;
       virtual void update(const std::string& state_name, bool auto_mode_status) = 0;
};

class DashboardDisplay : public IHeadlightObserver {
public:
    void update(const std::string& state_name, bool auto_mode_status) override {
        std::cout << "\n[DASHBOARD UPDATE] ---" << std::endl;
        std::cout << "  Headlight Status: " << state_name << std::endl;
        std::cout << "  Auto Mode Icon:   " << (auto_mode_status ? "[A]" : "---") << std::endl;
        std::cout << "----------------------" << std::endl;
    }
};

// --- 2. Diagnostic Logger Observer ---
// Simulates the background logging service for fault detection and historical data
class DiagnosticLogger : public IHeadlightObserver {
public:
    void update(const std::string& state_name, bool auto_mode_status) override {
        // In a real system, this would write to persistent memory (EEPROM/flash)
        std::cout << "[DIAGNOSTIC LOG] New state recorded: " << state_name 
                  << " | Auto Status: " << (auto_mode_status ? "ON" : "OFF") << std::endl;
    }
};




