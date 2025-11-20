To simulate the control logic for a vehicle component (e.g., an automated headlight system) using a formal State Machine and abstracting actions using the Command Pattern.

This demonstrates:

    State Management: Predictable behavior based on defined states.

    Decoupling: Separation of system logic (the State Machine) from the action implementation (the Command objects).

    Testability: Actions can be tested in isolation.

   
State Pattern,Defines system behavior based on its internal state.,"HeadlightState abstract base class and derived classes (Off, LowBeam, HighBeam)."
Command Pattern,Encapsulates an action or request as an object.,"ICommand abstract base class and concrete command classes (IncreaseIntensityCommand, ToggleAutoModeCommand)."