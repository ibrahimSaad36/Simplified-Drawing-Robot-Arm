# Old Design Issues

## Overview

This document outlines the known issues with the old design of `Simplified Drawing Robot Arm` application. This is the first and important step to be able to refactor the codebase and improve the overall architecture.

I will be updating this document as I identify more issues and as I make progress on the refactoring. The main focus will be on applying the SOLID principles to ensure that the new design is modular, maintainable, and scalable. Also, we will be looking into implementing design patterns where applicable to enhance the structure and readability of the code.

Let's start with ImageProcessing class, which is a central part of our application and has several design flaws that need to be addressed.

## ImageProcessing Class Issues

### 1. Single Responsibility Principle Violation

**Remember**: The Single Responsibility Principle (SRP) states that a class should have only one reason to change, meaning it should only have one job or responsibility.

SRP applies somehow for this class, as it's responsible for doing processing on the given image but it also handles file I/O operations, which should be separated out. This violates the Single Responsibility Principle, for example, the constructor `ImageProcessing` does the following:

- Loads the image from the given path
- Trying to read the image file
- Saves the read image to a member variable

This this should not happen, the class should onlt do some processing on the image and just it.

Also, in `faceDetected` method, it tries to load an XML file, this should be handled else where.

### 2. Dependency Inversion Violation

**Remember**: The Dependency Inversion Principle (DIP) states that high-level modules should not depend on low-level modules, both should depend on abstractions. Additionally, abstractions should not depend on details, details should depend on abstractions.

- The `ImageProcessing` class directly depends on the `OpenCV` library for image processing tasks. This creates a tight coupling between the application and the specific library, making it difficult to replace or mock for testing purposes. Instead, we should introduce an abstraction layer (interface) that defines the operations needed for image processing, allowing us to swap out implementations without affecting the rest of the codebase.

- Also the class use UI elements directly, which is not a good practice. The class should not depend on UI elements, instead it should use an abstraction to communicate with the UI. This is shown in the `faceDetected` method where it tries to use `QMessageBox` directly. This should be handled by a separate class or a service that communicates with the UI.

### 3. Open/Closed Principle Violation

**Remember**: The Open/Closed Principle (OCP) states that software entities should be open for extension but closed for modification.

The `ImageProcessing` class is not designed to be easily extensible. For example, if we want to add support for a new image processing algorithm, we would have to modify the existing class, which violates the OCP. Instead, we should use interfaces or abstract classes to define the contract for image processing operations, allowing us to create new implementations without modifying the existing code. This is also can be shown in using Gaussian blur in the `imageContoursOnly` method, which is hardcoded and not easily extensible. Also some member variables are either hardcoded or initialized with hardcoded values, which makes it difficult to change the behavior of the class without modifying the code.

### 4. Too Many Public Member Variables

**Remember**: Classes should encapsulate their data and expose only what is necessary through public methods.

The `ImageProcessing` class has too many public member variables, which exposes its internal state and makes it difficult to maintain. This violates the principle of encapsulation. Instead, we should use private member variables and provide public methods to access or modify them as needed. For example, the `image` and `imageContours` member variables should be private, and we should provide getter methods to access them if necessary.

This should be handled in the design, if the same object (same image) need to be used in multiple places in the code, we can use a singleton pattern instead of leaving
all the class members public which is absolutely wrong.

## SerialCommunication Class Issues

### 1- Single Responsibility Principle Violation

**Remember**: The Single Responsibility Principle (SRP) states that a class should have only one reason to change. Meaning it should only have one job or responsibility.

The `SerialCommunication` class is responsible for both managing the serial communication with the robot arm and handling the data processing logic (preparing the contours to be in the suitable format before sending). This violates the SRP, as it has multiple responsibilities. We should separate the concerns of serial communication and data processing into different classes or services.

Also the class uses UI elements like `QProgressDialog` directly to update the progress of sending, which is not a good practice. This is not the responsibility of the `SerialCommunication` class.

The class acts if it will send only contours, but it should be able to send any data, so the class should be more generic and not tied to a specific data type. It may be better to recieve serialized data as a container of bytes ready to be sent.

### 2- Dependency Inversion Violation

**Remember**: The Dependency Inversion Principle (DIP) states that high-level modules should not depend on low-level modules, both should depend on abstractions.

The `SerialCommunication` class owns Windows-specific serial communication code and types like `HANDLE` and `DCB` and so on, which creates a tight coupling between the application and the specific platform. This makes it difficult to test or replace the serial communication implementation. Instead, we should introduce an abstraction layer (interface) that defines the operations needed for serial communication, allowing us to swap out implementations without affecting the rest of the codebase.

It will be more better if we used an interface which defines generic methods to be used via any communication protocol, not just serial communication. This will allow us to use the same interface for other communication protocols in the future.

The class also depends on `OpenCV` types like `cv::Point`, this is not good practice as it creates a tight coupling between the application and the specific library. Instead, we should use our own data types or abstractions to represent the data being sent.

Also it uses UI elements like `QMessageBox` and `QProgressBar` directly, which is not a good practice. The class should not depend on UI elements, instead it should use an abstraction to communicate with the UI. This is shown in the `sendContours` method where it tries to use `QMessageBox` directly. This should be handled by a separate class or a service that communicates with the UI.

### 3- Open/Closed Principle Violation

**Remember**: The Open/Closed Principle (OCP) states that software entities should be open for extension but closed for modification.

The `SerialCommunication` class is not designed to be easily extensible. For example, if we want to add support for a new communication protocol, we would have to modify the existing class, which violates the OCP. Instead, we should use interfaces or abstract classes to define the contract for serial communication operations, allowing us to create new implementations without modifying the existing code.

## SendingData Class Issues

### 1: Single Responsibility Principle Violation

**Remember**: The Single Responsibility Principle (SRP) states that a class should have only one reason to change, meaning it should only have one job or responsibility.

The class is responsiple for both deciding which if to take the contours resulting from image after canny or the contours of the original image directly, and also for sending the data to the robot arm using `SerialCommunication` class. This violates the SRP, as it has multiple responsibilities. We should separate the concerns of deciding which data to send and sending the data into different classes or services.

### 2: Dependency Inversion Violation

**Remember**: The Dependency Inversion Principle (DIP) states that high-level modules should not depend on low-level modules, both should depend on abstractions.

The `SendingData` class directly depends on the `ImageProcessing` to get the contours data and `SerialCommunication` to send the contours, which creates a tight coupling between the application and these specific implementations. Instead, we should introduce an abstraction layer (interface) that defines the operations needed for image processing and serial communication, allowing us to swap out implementations without affecting the rest of the codebase.

## CustomizeCannyDetection Class Issues

### (1) Dependency Inversion Violation

**Remember**: The Dependency Inversion Principle (DIP) states that high-level modules should not depend on low-level modules, both should depend on abstractions.

The `CustomizeCannyDetection` class directly depends on the `ImageProcessing` class to manipulate the max and minimum threshold for the canny detection, which creates a tight coupling between the application and this specific implementation. Instead, we should introduce an abstraction layer (interface) that defines the operations needed for image processing, allowing us to swap out implementations without affecting the rest of the codebase.

## Conclusion

This document outlines the main design issues with the old `Simplified Drawing Robot Arm` application. The identified issues primarily revolve around violations of the SOLID principles, particularly the Single Responsibility Principle, Dependency Inversion Principle, and Open/Closed Principle. The next steps will involve refactoring the design to address these issues, applying the SOLID principles, and introducing design patterns where applicable to enhance the structure and readability of the code.
