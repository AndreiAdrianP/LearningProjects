Static Factory Method: Short Summary

The Static Factory Method is a Creational Design Pattern used to simplify the process of object creation by centralizing instantiation logic within a single static method.

Core Principles

Intent: To encapsulate the object creation process, allowing client code to request an object by specifying its type (often via an enum or string) without knowing the specific, concrete class name it needs.

Mechanism: A dedicated Factory class provides a single, public, static method (the Factory Method, e.g., createVehicle()).

Decoupling: The client interacts only with the static factory method and the base Interface/Abstract Class (e.g., Vehicle). This decouples the client from the product's construction details.

Key Advantages

Centralized Control: All new operations are hidden inside the factory method, making code easier to maintain if product classes change.

Encapsulation: Client code is shielded from the product hierarchy, promoting the Program to an Interface, not an Implementation principle.

Simplicity: Since the method is static, you do not need to instantiate the factory class itself to use it.