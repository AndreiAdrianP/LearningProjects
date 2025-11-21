#pragma once
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "HeadLightSimulation.hpp" // Receiver

class ICommand {
public:
    // Virtual destructor defined here, implemented in the CPP file.
    virtual ~ICommand() = default; 
    
    // Command executes itself on the Receiver (HeadlightContext)
    virtual void execute(HeadlightContext& context) = 0;
    virtual std::string get_name() const = 0;
};

// --- Concrete Command Implementations (Declarations Only) ---

class ToggleLowBeamCommand : public ICommand {
public:
    void execute(HeadlightContext& context) override; // Declaration only
    std::string get_name() const override; // Declaration only
};

class ToggleHighBeamCommand : public ICommand {
public:
    void execute(HeadlightContext& context) override; // Declaration only
    std::string get_name() const override; // Declaration only
};

class SwitchOffCommand : public ICommand {
public:
    void execute(HeadlightContext& context) override; // Declaration only
    std::string get_name() const override; // Declaration only
};

class ToggleAutoModeCommand : public ICommand {
public:
    void execute(HeadlightContext& context) override; // Declaration only
    std::string get_name() const override; // Declaration only
};

// Declaration for the utility function (defined in ICommand.cpp)
void execute_commands(HeadlightContext& context, const std::vector<std::unique_ptr<ICommand>>& commands);