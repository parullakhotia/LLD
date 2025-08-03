# Uber System Design - SDE1 Interview Guide

## Table of Contents
1. [System Overview](#system-overview)
2. [Requirements Analysis](#requirements-analysis)
3. [Entity Modeling](#entity-modeling)
4. [System Architecture](#system-architecture)
5. [Database Design](#database-design)
6. [Key Workflows](#key-workflows)
7. [Design Patterns](#design-patterns)
8. [Technical Considerations](#technical-considerations)
9. [Interview Flow](#interview-flow)

---

## System Overview

Uber is a **ride-sharing platform** that connects riders with drivers for transportation services.

### Core Features:
- User registration and authentication
- Ride booking and matching
- Real-time tracking
- Payment processing
- Rating and review system
- Driver onboarding

---

## Requirements Analysis

### Functional Requirements:
1. **User Management**
   - Rider registration and profile management
   - Driver registration and verification
   - Authentication and authorization

2. **Ride Booking**
   - Location-based ride requests
   - Driver matching and assignment
   - Real-time ride tracking
   - Ride completion and payment

3. **Payment System**
   - Multiple payment methods
   - Fare calculation
   - Driver earnings management
   - Refund processing

4. **Rating System**
   - Driver-rider ratings
   - Review management
   - Quality control

### Non-Functional Requirements:
- **Scalability**: Handle millions of concurrent users
- **Availability**: 99.9% uptime
- **Latency**: < 200ms for ride requests
- **Reliability**: No data loss
- **Security**: Secure payment and user data

---

## Entity Modeling

### Core Entities:

#### 1. User (Rider)
```
Attributes:
- id, name, email, phone, address
- payment_methods, preferences
- rating, total_rides, member_since
- current_location (lat, lng)
```

#### 2. Driver
```
Attributes:
- id, name, phone, license_number
- vehicle_details, documents
- rating, total_rides, earnings
- current_location, status (online/offline)
- verification_status
```

#### 3. Vehicle
```
Attributes:
- id, license_plate, model, year
- color, capacity, features
- driver_id, insurance_info
- maintenance_status
```

#### 4. Ride
```
Attributes:
- id, rider_id, driver_id, vehicle_id
- pickup_location, dropoff_location
- status, fare, distance, duration
- created_at, completed_at
- payment_status
```

#### 5. Payment
```
Attributes:
- id, ride_id, amount, method
- status, transaction_id
- driver_share, uber_commission
- timestamp
```

### ER Diagram:

```
┌─────────────┐     ┌─────────────┐     ┌─────────────┐
│    User     │     │   Driver    │     │   Vehicle   │
│             │     │             │     │             │
│ id (PK)     │     │ id (PK)     │     │ id (PK)     │
│ name        │     │ name        │     │ license_plate│
│ email       │     │ phone       │     │ model       │
│ phone       │     │ license_num │     │ driver_id   │
│ rating      │     │ rating      │     │ (FK)        │
│ location    │     │ status      │     └─────────────┘
└─────────────┘     │ location    │             │
       │            └─────────────┘             │
       │                   │                   │
       │                   │                   │
       └───────────────────┼───────────────────┘
                           │
                    ┌─────────────┐
                    │    Ride     │
                    │             │
                    │ id (PK)     │
                    │ rider_id    │
                    │ driver_id   │
                    │ vehicle_id  │
                    │ pickup_loc  │
                    │ dropoff_loc │
                    │ status      │
                    │ fare        │
                    └─────────────┘
                           │
                    ┌─────────────┐
                    │   Payment   │
                    │             │
                    │ id (PK)     │
                    │ ride_id (FK)│
                    │ amount      │
                    │ method      │
                    │ status      │
                    └─────────────┘
```

### Relationships:
```
User (1) ----requests----> Ride (many)
Driver (1) ----provides----> Ride (many)
Vehicle (1) ----used_for----> Ride (many)
Ride (1) ----has----> Payment (1)
Driver (1) ----owns----> Vehicle (many)
```

---

## System Architecture

### High-Level Architecture:

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Mobile App    │    │   Web Portal    │    │  Driver App     │
└─────────────────┘    └─────────────────┘    └─────────────────┘
         │                       │                       │
         └───────────────────────┼───────────────────────┘
                                 │
                    ┌─────────────────┐
                    │   API Gateway   │
                    └─────────────────┘
                                 │
         ┌───────────────────────┼───────────────────────┐
         │                       │                       │
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│  User Service   │    │  Driver Service │    │  Ride Service   │
└─────────────────┘    └─────────────────┘    └─────────────────┘
         │                       │                       │
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│ Payment Service │    │ Location Service│    │ Notification    │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

### Microservices Breakdown:

1. **User Service**: Rider management and profiles
2. **Driver Service**: Driver management and verification
3. **Ride Service**: Ride booking and matching
4. **Payment Service**: Payment processing
5. **Location Service**: Geospatial queries and routing
6. **Notification Service**: Push notifications and alerts
7. **Rating Service**: Reviews and ratings management

---

## Database Design

### Core Tables:

#### 1. Users Table
```sql
CREATE TABLE users (
    id VARCHAR(36) PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    email VARCHAR(100) UNIQUE NOT NULL,
    phone VARCHAR(15) UNIQUE NOT NULL,
    address TEXT,
    location_lat DECIMAL(10,8),
    location_lng DECIMAL(11,8),
    rating DECIMAL(3,2) DEFAULT 0.0,
    total_rides INT DEFAULT 0,
    member_since TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    status ENUM('ACTIVE', 'INACTIVE', 'SUSPENDED') DEFAULT 'ACTIVE',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);
```

#### 2. Drivers Table
```sql
CREATE TABLE drivers (
    id VARCHAR(36) PRIMARY KEY,
    user_id VARCHAR(36) NOT NULL,
    license_number VARCHAR(50) UNIQUE NOT NULL,
    vehicle_id VARCHAR(36),
    rating DECIMAL(3,2) DEFAULT 0.0,
    total_rides INT DEFAULT 0,
    earnings DECIMAL(10,2) DEFAULT 0.0,
    status ENUM('ONLINE', 'OFFLINE', 'BUSY') DEFAULT 'OFFLINE',
    verification_status ENUM('PENDING', 'VERIFIED', 'REJECTED') DEFAULT 'PENDING',
    documents JSON,
    current_location_lat DECIMAL(10,8),
    current_location_lng DECIMAL(11,8),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (vehicle_id) REFERENCES vehicles(id)
);
```

#### 3. Vehicles Table
```sql
CREATE TABLE vehicles (
    id VARCHAR(36) PRIMARY KEY,
    driver_id VARCHAR(36) NOT NULL,
    license_plate VARCHAR(20) UNIQUE NOT NULL,
    model VARCHAR(100) NOT NULL,
    year INT NOT NULL,
    color VARCHAR(50),
    capacity INT DEFAULT 4,
    features JSON,
    insurance_info JSON,
    maintenance_status ENUM('GOOD', 'MAINTENANCE_DUE', 'OUT_OF_SERVICE') DEFAULT 'GOOD',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (driver_id) REFERENCES drivers(id)
);
```

#### 4. Rides Table
```sql
CREATE TABLE rides (
    id VARCHAR(36) PRIMARY KEY,
    rider_id VARCHAR(36) NOT NULL,
    driver_id VARCHAR(36),
    vehicle_id VARCHAR(36),
    pickup_lat DECIMAL(10,8) NOT NULL,
    pickup_lng DECIMAL(11,8) NOT NULL,
    dropoff_lat DECIMAL(10,8) NOT NULL,
    dropoff_lng DECIMAL(11,8) NOT NULL,
    status ENUM('REQUESTED', 'ACCEPTED', 'STARTED', 'COMPLETED', 'CANCELLED') DEFAULT 'REQUESTED',
    fare DECIMAL(10,2),
    distance DECIMAL(8,2),
    duration INT,
    payment_status ENUM('PENDING', 'PAID', 'REFUNDED') DEFAULT 'PENDING',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    started_at TIMESTAMP NULL,
    completed_at TIMESTAMP NULL,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (rider_id) REFERENCES users(id),
    FOREIGN KEY (driver_id) REFERENCES drivers(id),
    FOREIGN KEY (vehicle_id) REFERENCES vehicles(id)
);
```

#### 5. Payments Table
```sql
CREATE TABLE payments (
    id VARCHAR(36) PRIMARY KEY,
    ride_id VARCHAR(36) NOT NULL,
    amount DECIMAL(10,2) NOT NULL,
    method ENUM('CREDIT_CARD', 'DEBIT_CARD', 'WALLET', 'CASH') NOT NULL,
    status ENUM('PENDING', 'SUCCESS', 'FAILED', 'REFUNDED') DEFAULT 'PENDING',
    transaction_id VARCHAR(100),
    driver_share DECIMAL(10,2),
    uber_commission DECIMAL(10,2),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (ride_id) REFERENCES rides(id)
);
```

#### 6. Ratings Table
```sql
CREATE TABLE ratings (
    id VARCHAR(36) PRIMARY KEY,
    ride_id VARCHAR(36) NOT NULL,
    rated_by ENUM('RIDER', 'DRIVER') NOT NULL,
    rating INT CHECK (rating >= 1 AND rating <= 5),
    comment TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    FOREIGN KEY (ride_id) REFERENCES rides(id)
);
```

---

## Key Workflows

### 1. Ride Booking Flow

```cpp
class RideBookingWorkflow {
private:
    std::shared_ptr<RideService> rideService;
    std::shared_ptr<LocationService> locationService;
    std::shared_ptr<NotificationService> notificationService;
    std::shared_ptr<PaymentService> paymentService;

public:
    std::string requestRide(const RideRequest& request) {
        // 1. Validate request
        if (!validateRideRequest(request)) {
            throw std::runtime_error("Invalid ride request");
        }
        
        // 2. Find nearby drivers
        auto nearbyDrivers = locationService->findNearbyDrivers(
            request.pickupLocation, 
            request.radius
        );
        
        if (nearbyDrivers.empty()) {
            throw std::runtime_error("No drivers available");
        }
        
        // 3. Calculate fare
        double fare = calculateFare(request.pickupLocation, request.dropoffLocation);
        
        // 4. Create ride request
        auto ride = std::make_shared<Ride>(request, fare);
        std::string rideId = rideService->createRide(ride);
        
        // 5. Send notifications to drivers
        notificationService->notifyDrivers(nearbyDrivers, ride);
        
        // 6. Send confirmation to rider
        notificationService->notifyRider(request.riderId, "RIDE_REQUESTED", ride);
        
        return rideId;
    }
    
    void acceptRide(const std::string& rideId, const std::string& driverId) {
        // 1. Update ride status
        rideService->acceptRide(rideId, driverId);
        
        // 2. Update driver status
        rideService->updateDriverStatus(driverId, "BUSY");
        
        // 3. Send notifications
        auto ride = rideService->getRide(rideId);
        notificationService->notifyRider(ride->getRiderId(), "RIDE_ACCEPTED", ride);
        
        // 4. Start real-time tracking
        locationService->startTracking(rideId);
    }
    
    void startRide(const std::string& rideId) {
        // 1. Update ride status
        rideService->startRide(rideId);
        
        // 2. Start fare calculation
        rideService->startFareCalculation(rideId);
        
        // 3. Send notifications
        auto ride = rideService->getRide(rideId);
        notificationService->notifyRider(ride->getRiderId(), "RIDE_STARTED", ride);
    }
    
    void completeRide(const std::string& rideId) {
        // 1. Calculate final fare
        double finalFare = rideService->calculateFinalFare(rideId);
        
        // 2. Update ride status
        rideService->completeRide(rideId, finalFare);
        
        // 3. Process payment
        paymentService->processPayment(rideId, finalFare);
        
        // 4. Update driver earnings
        rideService->updateDriverEarnings(rideId);
        
        // 5. Request ratings
        auto ride = rideService->getRide(rideId);
        notificationService->requestRating(ride);
        
        // 6. Update driver status
        rideService->updateDriverStatus(ride->getDriverId(), "ONLINE");
    }
};
```

### 2. Driver Onboarding Flow

```cpp
class DriverOnboardingWorkflow {
private:
    std::shared_ptr<DriverService> driverService;
    std::shared_ptr<VerificationService> verificationService;
    std::shared_ptr<NotificationService> notificationService;

public:
    std::string onboardDriver(const DriverOnboardingRequest& request) {
        // 1. Create user account
        auto user = std::make_shared<User>(request.userData);
        std::string userId = driverService->createUser(user);
        
        // 2. Create driver profile
        auto driver = std::make_shared<Driver>(request.driverData);
        driver->setUserId(userId);
        std::string driverId = driverService->createDriver(driver);
        
        // 3. Add vehicle information
        auto vehicle = std::make_shared<Vehicle>(request.vehicleData);
        vehicle->setDriverId(driverId);
        driverService->addVehicle(vehicle);
        
        // 4. Upload documents
        for (const auto& document : request.documents) {
            driverService->uploadDocument(driverId, document);
        }
        
        // 5. Initiate background check
        verificationService->initiateBackgroundCheck(driverId);
        
        // 6. Send welcome notification
        notificationService->notifyDriver(driverId, "WELCOME", {});
        
        return driverId;
    }
    
    void verifyDriver(const std::string& driverId) {
        // 1. Update verification status
        driverService->updateVerificationStatus(driverId, "VERIFIED");
        
        // 2. Activate driver
        driverService->activateDriver(driverId);
        
        // 3. Send verification notification
        notificationService->notifyDriver(driverId, "VERIFIED", {});
        
        // 4. Update availability
        driverService->updateAvailability(driverId, true);
    }
};
```

---

## Design Patterns

### 1. Strategy Pattern - Payment Methods

```cpp
class PaymentStrategy {
public:
    virtual ~PaymentStrategy() = default;
    virtual bool processPayment(double amount, const std::string& currency) = 0;
    virtual std::string getPaymentMethod() const = 0;
};

class CreditCardStrategy : public PaymentStrategy {
public:
    bool processPayment(double amount, const std::string& currency) override {
        // Credit card processing logic
        return true;
    }
    std::string getPaymentMethod() const override { return "CreditCard"; }
};

class WalletStrategy : public PaymentStrategy {
public:
    bool processPayment(double amount, const std::string& currency) override {
        // Wallet processing logic
        return true;
    }
    std::string getPaymentMethod() const override { return "Wallet"; }
};
```

### 2. State Pattern - Ride States

```cpp
class RideState {
public:
    virtual ~RideState() = default;
    virtual void handle(Ride* ride) = 0;
    virtual std::string getStateName() const = 0;
    virtual bool canTransitionTo(const std::string& newState) const = 0;
};

class RequestedState : public RideState {
public:
    void handle(Ride* ride) override {
        // Send notifications to nearby drivers
    }
    std::string getStateName() const override { return "REQUESTED"; }
    bool canTransitionTo(const std::string& newState) const override {
        return newState == "ACCEPTED" || newState == "CANCELLED";
    }
};

class AcceptedState : public RideState {
public:
    void handle(Ride* ride) override {
        // Notify rider and start tracking
    }
    std::string getStateName() const override { return "ACCEPTED"; }
    bool canTransitionTo(const std::string& newState) const override {
        return newState == "STARTED" || newState == "CANCELLED";
    }
};

class StartedState : public RideState {
public:
    void handle(Ride* ride) override {
        // Start fare calculation and tracking
    }
    std::string getStateName() const override { return "STARTED"; }
    bool canTransitionTo(const std::string& newState) const override {
        return newState == "COMPLETED" || newState == "CANCELLED";
    }
};

class CompletedState : public RideState {
public:
    void handle(Ride* ride) override {
        // Process payment and request ratings
    }
    std::string getStateName() const override { return "COMPLETED"; }
    bool canTransitionTo(const std::string& newState) const override {
        return false; // Final state
    }
};
```

### 3. Observer Pattern - Real-time Updates

```cpp
class LocationObserver {
public:
    virtual ~LocationObserver() = default;
    virtual void updateLocation(const std::string& rideId, double lat, double lng) = 0;
};

class NotificationObserver : public LocationObserver {
public:
    void updateLocation(const std::string& rideId, double lat, double lng) override {
        // Send real-time location updates to rider
        std::cout << "Sending location update for ride: " << rideId << std::endl;
    }
};

class TrackingObserver : public LocationObserver {
public:
    void updateLocation(const std::string& rideId, double lat, double lng) override {
        // Update ride tracking information
        std::cout << "Updating tracking for ride: " << rideId << std::endl;
    }
};
```

---

## Technical Considerations

### 1. Scalability
- **Microservices architecture** for independent scaling
- **Database sharding** by location/region
- **Caching** for frequently accessed data
- **Load balancing** for API requests

### 2. Performance
- **Geospatial indexing** for location-based queries
- **Real-time tracking** using WebSockets
- **Payment processing** with retry mechanisms
- **Background job processing** for notifications

### 3. Reliability
- **Circuit breakers** for external service calls
- **Retry mechanisms** for failed operations
- **Data consistency** with distributed transactions
- **Monitoring and alerting** for system health

### 4. Security
- **JWT tokens** for authentication
- **Role-based access control** (RBAC)
- **Data encryption** at rest and in transit
- **Rate limiting** for API protection

---

## Interview Flow

### Step 1: Clarify Requirements (2 minutes)
```
❓ "Let me understand the requirements first..."
- What are the main features?
- What's the scale (users, rides per day)?
- Any specific constraints?
- What's the primary use case?
```

### Step 2: Identify Entities (1 minute)
```
✅ "The main entities are:"
- User (Rider)
- Driver
- Vehicle
- Ride
- Payment
- Rating
```

### Step 3: Design Database (2 minutes)
```
✅ "I'll design the database with these tables:"
- Users table for riders
- Drivers table for drivers
- Vehicles table for vehicle info
- Rides table for ride details
- Payments table for transactions
- Ratings table for reviews
```

### Step 4: Choose Architecture (2 minutes)
```
✅ "I'll use microservices architecture:"
- User Service for rider management
- Driver Service for driver management
- Ride Service for ride booking
- Payment Service for transactions
- Location Service for geospatial queries
- Notification Service for alerts
```

### Step 5: Explain Workflows (2 minutes)
```
✅ "The key workflows are:"
- Ride booking flow
- Driver onboarding flow
- Payment processing flow
- Real-time tracking flow
```

### Step 6: Discuss Patterns (1 minute)
```
✅ "I'll use these design patterns:"
- Strategy Pattern for payment methods
- State Pattern for ride states
- Observer Pattern for real-time updates
- Factory Pattern for service creation
```

### Step 7: Address Concerns (1 minute)
```
✅ "For scalability and performance:"
- Database sharding by location
- Caching for frequent queries
- Load balancing for high traffic
- Real-time updates via WebSockets
```

---

## Key Interview Tips

### Do's:
- ✅ Start with requirements clarification
- ✅ Draw diagrams and explain them
- ✅ Discuss trade-offs and alternatives
- ✅ Consider edge cases and error handling
- ✅ Mention scalability and performance

### Don'ts:
- ❌ Jump straight into implementation
- ❌ Ignore non-functional requirements
- ❌ Forget about error handling
- ❌ Over-engineer simple problems
- ❌ Ignore security considerations

### Always Mention:
- ✅ Error handling and edge cases
- ✅ Scalability considerations
- ✅ Security aspects
- ✅ Performance optimization
- ✅ Monitoring and logging

---

## Conclusion

This Uber system design demonstrates:

1. **Clear understanding of requirements**
2. **Proper entity modeling and relationships**
3. **Scalable microservices architecture**
4. **Appropriate use of design patterns**
5. **Production-ready technical considerations**

The design is **interview-ready** and shows systematic thinking suitable for an SDE1 position. 