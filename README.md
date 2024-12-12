# Service Management System

## Introduction
The Service Management System is a console-based application written in C++ that allows users to manage services, users, and service providers. Users can request services, rate service providers, and view details about services and providers.

## Features
1. **Add Services**: Allows administrators to add new services to the system.
2. **Add Users**: Enables the registration of new users with unique contact information.
3. **Add Service Providers**: Allows administrators to add service providers, define their hourly rates, and associate them with specific services.
4. **Display Service Providers**: Lists all service providers offering a specific service, along with their hourly rates and ratings.
5. **Request Services**: Users can request services from specific service providers, specifying the number of hours required.
6. **Rate Service Providers**: Users can rate service providers after availing of their services.

## Requirements
- **Compiler**: Any C++ compiler with C++11 or higher support.
- **Libraries**: Standard C++ libraries (`iostream`, `vector`, `string`, `unordered_set`, `iomanip`).

## How to Run
1. Compile the program using a C++ compiler:
   ```
   g++ -o ServiceManagementSystem ServiceManagementSystem.cpp
   ```
2. Run the executable:
   ```
   ./ServiceManagementSystem
   ```
3. Follow the on-screen menu to interact with the system.

## Menu Options
- **1. Add Service**: Adds a new service. You will be prompted for the service name and whether it uses its own materials.
- **2. Add User**: Registers a new user. You will be prompted for the user’s name and contact information.
- **3. Add Service Provider**: Adds a new service provider. You will be prompted for the provider's name, contact information, hourly rate, and the services they offer.
- **4. Display Service Providers for a Service**: Lists service providers offering a specific service, along with their details.
- **5. Request Service**: Allows a user to request a service from a service provider. The user must provide their user ID, the desired service, the provider, and the required hours.
- **6. Rate Service Provider**: Allows users to rate a service provider after availing of their services. Users can provide a rating between 1 and 5.
- **7. Exit**: Exits the application.

## Classes and Their Responsibilities
### 1. `Service`
- Abstract base class representing a generic service.
- Contains virtual methods for calculating cost and displaying details.

### 2. `CleaningService` (Derived from `Service`)
- Represents a specific cleaning service.
- Includes additional details such as whether the service uses its own materials.

### 3. `UserProfile`
- Stores information about a user, including name, contact, and user ID.
- Provides methods to display user details.

### 4. `ServiceProvider`
- Represents a service provider.
- Stores information about the provider’s name, contact, hourly rate, and services offered.
- Maintains ratings and calculates the average rating.

### 5. `ServiceRequest`
- Represents a service request made by a user.
- Stores information about the user, service provider, requested service, and number of hours.

### 6. `ServiceManagementSystem`
- Core system class managing services, users, service providers, and service requests.
- Contains methods for adding and retrieving entities, and verifying user registration.

### 7. `ServiceApplication`
- User interface class that interacts with the `ServiceManagementSystem`.
- Contains menu-driven methods to perform actions like adding services, users, providers, requesting services, and rating providers.

## Example Usage
1. **Adding a Service**:
   - Select option 1 from the menu.
   - Enter service name (e.g., `Cleaning`).
   - Specify whether the service uses its own materials (1 for yes, 0 for no).

2. **Adding a User**:
   - Select option 2 from the menu.
   - Enter user name and contact information.

3. **Adding a Service Provider**:
   - Select option 3 from the menu.
   - Enter provider name, contact, hourly rate, and services offered.

4. **Requesting a Service**:
   - Select option 5 from the menu.
   - Provide user ID, service name, provider name, and the number of hours required.

5. **Rating a Service Provider**:
   - Select option 6 from the menu.
   - Enter user ID, provider name, and rating (1-5).

## Notes
- Ensure that services, users, and providers are added before requesting a service.
- User contacts must be unique to avoid duplication.
- Ratings can only be provided by users who have requested a service from the provider.

## Future Enhancements
- Add support for more types of services.
- Implement persistent storage for services, users, and providers.
- Enhance user input validation and error handling.
- Provide a graphical user interface (GUI) for improved user experience.

## Author
- Developed by YASH


