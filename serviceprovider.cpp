#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <iomanip>

using namespace std;

class Service {
public:
    Service(const string& name)
        : name(name) {}
    virtual ~Service() {}

    virtual double calculateCost(int hours, double hourlyRate) const = 0;

    virtual void displayDetails() const {
        cout << "Service: " << name << endl;
    }

    string getName() const {
        return name;
    }

protected:
    string name;
};

class CleaningService : public Service {
public:
    CleaningService(const string& name, bool usesOwnMaterials)
        : Service(name), usesOwnMaterials(usesOwnMaterials) {}

    double calculateCost(int hours, double hourlyRate) const override {
        double materialCost = usesOwnMaterials ? 20.0 : 0.0;
        return hours * hourlyRate + materialCost;
    }

    void displayDetails() const override {
        Service::displayDetails();
        cout << "Uses Own Materials: " << (usesOwnMaterials ? "Yes" : "No") << endl;
    }

private:
    bool usesOwnMaterials;
};

class UserProfile {
public:
    UserProfile(const string& name, const string& contact, int userId)
        : name(name), contact(contact), userId(userId) {}

    void displayProfile() const {
        cout << "User Profile:" << endl;
        cout << "User ID: " << userId << endl;
        cout << "Name: " << name << endl;
        cout << "Contact: " << contact << endl;
    }

    string getName() const {
        return name;
    }

    string getContact() const {
        return contact;
    }

    int getUserId() const {
        return userId;
    }

private:
    string name;
    string contact;
    int userId;
};

class ServiceProvider {
public:
    ServiceProvider(const string& name, const string& contact, double hourlyRate)
        : name(name), contact(contact), hourlyRate(hourlyRate) {}

    void addService(Service* service) {
        services.push_back(service);
    }

    double getHourlyRate() const {
        return hourlyRate;
    }

    void displayProfile() const {
        cout << "Service Provider Profile:" << endl;
        cout << "Name: " << name << endl;
        cout << "Contact: " << contact << endl;
        cout << "Hourly Rate: $" << fixed << setprecision(2) << hourlyRate << endl;
        cout << "Services offered:" << endl;
        for (const auto& service : services) {
            service->displayDetails();
        }
    }

    string getName() const {
        return name;
    }
    string getContact() const {
        return contact;
    }
    void addRating(int rating) {
        ratings.push_back(rating);
    }

    double getAverageRating() const {
        if (ratings.empty()) {
            return 0.0;
        }
        double sum = 0;
        for (int rating : ratings) {
            sum += rating;
        }
        return sum / ratings.size();
    }

    bool hasServiceRequestFrom(int userId) const {
        for (int id : userIDs) {
            if (id == userId) {
                return true;
            }
        }
        return false;
    }

    vector<Service*> getServices() const {
        return services;
    }

private:
    vector<int> ratings;
    vector<int> userIDs;
    string name;
    string contact;
    double hourlyRate;
    vector<Service*> services;
};

class ServiceRequest {
public:
    ServiceRequest(int userId, const ServiceProvider& provider, const Service* service, int hours)
        : userId(userId), provider(provider), service(service), hours(hours) {}

    void displayRequestDetails() const {
        cout << "Service Request Details:" << endl;
        cout << "User ID: " << userId << endl;
        provider.displayProfile();
        cout << "Requested Service: ";
        service->displayDetails();
        cout << "Hourly Rate: $" << fixed << setprecision(2) << provider.getHourlyRate() << endl;
        cout << "Hours: " << hours << endl;
    }
    int getUserId() const {
        return userId;
    }
    const ServiceProvider& getProvider() const {
        return provider;
    }

private:
    int userId;
    const ServiceProvider& provider;
    const Service* service;
    int hours;
};

class ServiceManagementSystem {
public:
    void addService(Service* service) {
        services.push_back(service);
    }

    void addUser(const UserProfile& user) {
        users.push_back(user);
        userSet.insert(user.getContact());
    }

    bool isUserRegistered(const string& contact) const {
        return userSet.find(contact) != userSet.end();
    }

    void addServiceProvider(ServiceProvider provider) {
        providers.push_back(provider);
    }

    void addServiceRequest(const ServiceRequest& request) {
        serviceRequests.push_back(request);
    }

    vector<ServiceProvider> getServiceProvidersForService(const string& serviceName) const {
        vector<ServiceProvider> providersForService;
        for (const ServiceProvider& provider : providers) {
            for (const Service* service : provider.getServices()) {
                if (service->getName() == serviceName) {
                    providersForService.push_back(provider);
                    break;
                }
            }
        }
        return providersForService;
    }

    vector<Service*> getServices() const {
        return services;
    }

    vector<UserProfile> getUsers() const {
        return users;
    }

    vector<ServiceProvider> getProviders() const {
        return providers;
    }
    vector<ServiceRequest> getServiceRequests() const {
        return serviceRequests;
    }

private:
    vector<ServiceRequest> serviceRequests;
    vector<Service*> services;
    vector<UserProfile> users;
    unordered_set<string> userSet;
    vector<ServiceProvider> providers;

};

class ServiceApplication {
private:
    ServiceManagementSystem sms;
    int userIdCounter = 1;

public:
    // Add services
    void addService() {
        string serviceName;
        bool usesOwnMaterials;
        cout << "Enter service name: ";
        cin >> serviceName;
        cout << "Does the service use its own materials? (1 for yes, 0 for no): ";
        cin >> usesOwnMaterials;

        sms.addService(new CleaningService(serviceName, usesOwnMaterials));
    }

    // Add users
    void addUser() {
        string userName, userContact;
        cout << "Enter user name: ";
        cin >> userName;
        do {
            cout << "Enter user contact: ";
            cin >> userContact;
        } while (sms.isUserRegistered(userContact));
        UserProfile user(userName, userContact, userIdCounter++);
        sms.addUser(user);
        user.displayProfile();
    }

    // Add service providers
    void addServiceProvider() {
        string providerName, providerContact;
        cout << "Enter service provider name: ";
        cin >> providerName;
        cout << "Enter service provider contact: ";
        cin >> providerContact;
        double hourlyRate;
        cout << "Enter hourly rate for services provided by " << providerName << ": ";
        cin >> hourlyRate;
        ServiceProvider provider(providerName, providerContact, hourlyRate);
        while (true) {
            cout << "Choose a service to offer (or enter 'done' to finish): ";
            string serviceName;
            cin >> serviceName;
            if (serviceName == "done") {
                break;
            }
            for (const Service* service : sms.getServices()) {
                if (service->getName() == serviceName) {
                    const CleaningService* cleaningService = dynamic_cast<const CleaningService*>(service);
                    if (cleaningService) {
                        provider.addService(new CleaningService(*cleaningService));
                        break;
                    }
                    else {
                        cout << "Failed to add service. Service is not a Cleaning Service." << endl;
                    }
                }
            }
        }
        sms.addServiceProvider(provider);
        provider.displayProfile();
    }

    // Display service providers for a specific service
    void displayServiceProvidersForService() const {
        cout << "Enter the service name to see available service providers: ";
        string serviceName;
        cin >> serviceName;
        vector<ServiceProvider> providersForService = sms.getServiceProvidersForService(serviceName);
        if (providersForService.empty()) {
            cout << "No service providers found for the specified service." << endl;
        }
        else {
            cout << "Service providers offering " << serviceName << " service:" << endl;
            for (size_t i = 0; i < providersForService.size(); ++i) {
                cout << i + 1 << ". " << providersForService[i].getName()
                    << " (Hourly Rate: $" << fixed << setprecision(2) << providersForService[i].getHourlyRate() << ")";

                // Display the provider's rating if available
                double averageRating = providersForService[i].getAverageRating();
                if (averageRating != 0) { // Use != 0 to include ratings of 0.0
                    cout << " - Rating: " << averageRating;
                }
                else {
                    cout << " - No ratings yet";
                }

                cout << endl;
            }
        }
    }



    // Request service from a provider
    void requestService() {
        if (sms.getServices().empty() || sms.getProviders().empty() || sms.getUsers().empty()) {
            cout << "Please add services, users, and service providers before requesting a service." << endl;
            return;
        }
        int userId;
        cout << "Enter your user ID: ";
        cin >> userId;
        bool userFound = false;
        UserProfile user("", "", 0);
        for (const UserProfile& userProfile : sms.getUsers()) {
            if (userProfile.getUserId() == userId) {
                user = userProfile;
                userFound = true;
                break;
            }
        }
        if (!userFound) {
            cout << "User with user ID " << userId << " not found." << endl;
            return;
        }
        string serviceName, providerName;
        int hours;
        cout << "Enter the desired service name: ";
        cin >> serviceName;
        vector<ServiceProvider> providersForService = sms.getServiceProvidersForService(serviceName);
        if (providersForService.empty()) {
            cout << "No service providers found for the specified service." << endl;
            return;
        }
        cout << "Choose a service provider from the list:" << endl;
        for (size_t i = 0; i < providersForService.size(); ++i) {
            cout << i + 1 << ". " << providersForService[i].getName() << " (Hourly Rate: $" << fixed << setprecision(2) << providersForService[i].getHourlyRate() << ")";

            // Display the provider's rating if available
            double averageRating = providersForService[i].getAverageRating();
            if (averageRating > 0) {
                cout << " - Rating: " << averageRating;
            }

            cout << endl;
        }

        size_t choice;
        cin >> choice;
        const ServiceProvider& selectedProvider = providersForService[choice - 1];
        if (choice > 0 && choice <= providersForService.size()) {
            cout << "Enter the number of hours needed for the service: ";
            cin >> hours;
            const Service* selectedService = providersForService[choice - 1].getServices()[0];
            ServiceRequest request(user.getUserId(), providersForService[choice - 1], selectedService, hours);
            sms.addServiceRequest(request);
            cout << "\nService request submitted successfully!" << endl;
            cout << "User Contact Information:" << endl;
            user.displayProfile();
            cout << "\nSelected Service Provider Details:" << endl;
            cout << "Name: " << selectedProvider.getName() << endl;
            cout << "Contact: " << selectedProvider.getContact() << endl;
            cout << "Hourly Rate: $" << fixed << setprecision(2) << selectedProvider.getHourlyRate() << endl;
            cout << "\nRequested Service Details:" << endl;
            selectedService->displayDetails();
            cout << "Hours: " << hours << endl;
        }
        else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    void rateServiceProvider() {
        int userId;
        cout << "Enter your user ID: ";
        cin >> userId;

        bool userFound = false;
        UserProfile user("", "", 0);

        // Find the user with the given user ID
        for (const UserProfile& userProfile : sms.getUsers()) {
            if (userProfile.getUserId() == userId) {
                user = userProfile;
                userFound = true;
                break;
            }
        }

        if (!userFound) {
            cout << "User with user ID " << userId << " not found." << endl;
            return;
        }

        string providerName;
        cout << "Enter the name of the service provider you want to rate: ";
        cin >> providerName;

        bool providerFound = false;
        ServiceProvider* providerPtr = nullptr; // Change to pointer to ServiceProvider

        // Find the service provider with the given name
        for (auto& provider : sms.getProviders()) { // Iterate over providers by reference
            if (provider.getName() == providerName) {
                providerFound = true;
                providerPtr = &provider; // Store the address of the found provider
                break;
            }
        }

        if (!providerFound) {
            cout << "Service provider with name " << providerName << " not found." << endl;
            return;
        }

        // Check if the user has requested a service from this provider
        bool serviceRequested = false;
        for (const auto& request : sms.getServiceRequests()) {
            if (request.getUserId() == userId && &(request.getProvider()) == providerPtr) { // Compare with the address of the found provider
                serviceRequested = true;
                break;
            }
        }

        if (!serviceRequested) {
            cout << "You must request a service from this provider at least once before rating." << endl;
            return;
        }

        int rating;
        cout << "Enter your rating (1-5) for the service provider: ";
        cin >> rating;

        if (rating < 1 || rating > 5) {
            cout << "Invalid rating. Rating must be between 1 and 5." << endl;
            return;
        }

        // Call addRating() method for the service provider
        providerPtr->addRating(rating); // Use the pointer to add rating
        cout << "Thank you for your rating!" << endl;
    }

};

int main() {
    ServiceApplication serviceApp;
    while (true) {
        cout << "\n1. Add Service\n";
        cout << "2. Add User\n";
        cout << "3. Add Service Provider\n";
        cout << "4. Display Service Providers for a Service\n";
        cout << "5. Request Service\n";
        cout << "6. Rate Service Provider\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
            serviceApp.addService();
            break;
        case 2:
            serviceApp.addUser();
            break;
        case 3:
            serviceApp.addServiceProvider();
            break;
        case 4:
            serviceApp.displayServiceProvidersForService();
            break;
        case 5:
            serviceApp.requestService();
            break;
        case 6:
            serviceApp.rateServiceProvider();
            break;
        case 7:
            cout << "Exiting the application. Goodbye!\n";
            return 0;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}