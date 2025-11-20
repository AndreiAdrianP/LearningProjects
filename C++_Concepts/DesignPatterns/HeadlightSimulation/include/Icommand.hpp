#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "HeadLightSimulation.hpp"

class ICommand {
public:
    virtual ~ICommand() = default;
    // Command executes itself on the Receiver (HeadlightContext)
    virtual void execute(HeadlightContext& context) = 0;
    virtual std::string get_name() const = 0;
};

// --- Concrete Command Implementations ---

class ToggleLowBeamCommand : public ICommand {
public:
    void execute(HeadlightContext& context) override {
        // The command translates the user/system intent into a state machine event.
        context.process_event("switch_to_low");
    }
    std::string get_name() const override { return "Toggle Low Beam"; }
};

class ToggleHighBeamCommand : public ICommand {
public:
    void execute(HeadlightContext& context) override {
        // High beams can only be toggled ON from low beams, or OFF from high beams.
        // We use two different events based on context, but let the State Machine handle the validity.
        context.process_event("switch_to_high"); 
    }
    std::string get_name() const override { return "Toggle High Beam"; }
};

class SwitchOffCommand : public ICommand {
public:
    void execute(HeadlightContext& context) override {
        context.process_event("switch_to_off");
    }
    std::string get_name() const override { return "Switch Off"; }
};

class ToggleAutoModeCommand : public ICommand {
public:
    void execute(HeadlightContext& context) override {
        context.process_event("toggle_auto");
    }
    std::string get_name() const override { return "Toggle Auto Mode"; }
};

void execute_commands(HeadlightContext& context, const std::vector<std::unique_ptr<ICommand>>& commands);