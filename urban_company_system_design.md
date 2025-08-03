# Urban Company System Design - Complete LLD

## Table of Contents
1. [System Overview](#system-overview)
2. [Entity Modeling](#entity-modeling)
3. [System Architecture](#system-architecture)
4. [Design Patterns](#design-patterns)
5. [Database Design](#database-design)
6. [Key Workflows](#key-workflows)
7. [Technical Considerations](#technical-considerations)
8. [Monitoring & Analytics](#monitoring--analytics)

---

## System Overview

Urban Company is a **home services marketplace** connecting customers with service professionals (beauticians, plumbers, electricians, etc.).

### Core Features:
- Service booking and scheduling
- Professional matching and allocation
- Real-time tracking
- Payment processing
- Rating and review system
- Professional onboarding

---

## Entity Modeling

### Core Entities:

#### 1. User/Customer
```
Attributes:
- id, name, email, phone, address
- preferences, payment_methods
- rating, total_orders, member_since
- location_coordinates
```

#### 2. Service Professional
```
Attributes:
- id, name, phone, skills, experience
- rating, total_jobs, availability
- location_coordinates, verification_status
- earnings, documents, background_check
```

#### 3. Service
```
Attributes:
- id, name, category, description
- base_price, duration, requirements
- is_active, popularity_score
```

#### 4. Booking/Order
```
Attributes:
- id, customer_id, professional_id, service_id
- scheduled_time, actual_time, status
- amount, payment_status, rating
- address, special_instructions
```

#### 5. Category
```
Attributes:
- id, name, description
- parent_category_id, icon_url
- is_active, display_order
```

#### 6. Payment
```
Attributes:
- id, booking_id, amount, method
- status, transaction_id, timestamp
- refund_status, gateway_response
```

### Relationships:
```
User (1) ----places----> Booking (many)
Professional (1) ----accepts----> Booking (many)
Service (1) ----booked_as----> Booking (many)
Category (1) ----contains----> Service (many)
Booking (1) ----has----> Payment (1)
Professional (many) ----provides----> Service (many)
```

---

## System Architecture

### High-Level Components:

```
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│   Mobile App    │    │   Web Portal    │    │  Admin Panel    │
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
│  User Service   │    │ Booking Service │    │ Payment Service │
└─────────────────┘    └─────────────────┘    └─────────────────┘
         │                       │                       │
┌─────────────────┐    ┌─────────────────┐    ┌─────────────────┐
│Professional Svc │    │  Notification   │    │  Rating Service │
└─────────────────┘    └─────────────────┘    └─────────────────┘
```

### Microservices Breakdown:

1. **User Service**: Customer and professional management
2. **Booking Service**: Order management and scheduling
3. **Payment Service**: Payment processing and refunds
4. **Professional Service**: Professional onboarding and management
5. **Notification Service**: Email, SMS, and push notifications
6. **Rating Service**: Reviews and ratings management
7. **Location Service**: Geospatial queries and routing
8. **Analytics Service**: Data aggregation and reporting

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

class UPIStrategy : public PaymentStrategy {
public:
    bool processPayment(double amount, const std::string& currency) override {
        // UPI processing logic
        return true;
    }
    std::string getPaymentMethod() const override { return "UPI"; }
};
```

### 2. State Pattern - Booking States

```cpp
class BookingState {
public:
    virtual ~BookingState() = default;
    virtual void handle(Booking* booking) = 0;
    virtual std::string getStateName() const = 0;
    virtual bool canTransitionTo(const std::string& newState) const = 0;
};

class PendingState : public BookingState {
public:
    void handle(Booking* booking) override {
        // Send notification to professionals
    }
    std::string getStateName() const override { return "PENDING"; }
    bool canTransitionTo(const std::string& newState) const override {
        return newState == "ACCEPTED" || newState == "CANCELLED";
    }
};

class AcceptedState : public BookingState {
public:
    void handle(Booking* booking) override {
        // Send confirmation to customer
    }
    std::string getStateName() const override { return "ACCEPTED"; }
    bool canTransitionTo(const std::string& newState) const override {
        return newState == "IN_PROGRESS" || newState == "CANCELLED";
    }
};
```

### 3. Observer Pattern - Notifications

```cpp
class NotificationObserver {
public:
    virtual ~NotificationObserver() = default;
    virtual void update(const std::string& event, const std::map<std::string, std::string>& data) = 0;
};

class NotificationSubject {
protected:
    std::vector<std::shared_ptr<NotificationObserver>> observers;

public:
    void attach(std::shared_ptr<NotificationObserver> observer) {
        observers.push_back(observer);
    }
    
    void notify(const std::string& event, const std::map<std::string, std::string>& data) {
        for (auto& observer : observers) {
            observer->update(event, data);
        }
    }
};

class EmailNotificationObserver : public NotificationObserver {
public:
    void update(const std::string& event, const std::map<std::string, std::string>& data) override {
        // Send email notification
        std::cout << "Sending email for event: " << event << std::endl;
    }
};

class SMSNotificationObserver : public NotificationObserver {
public:
    void update(const std::string& event, const std::map<std::string, std::string>& data) override {
        // Send SMS notification
        std::cout << "Sending SMS for event: " << event << std::endl;
    }
};
```

### 4. Factory Pattern - Service Creation

```cpp
class ServiceFactory {
public:
    static std::shared_ptr<Service> createService(const std::string& type, const std::map<std::string, std::string>& params) {
        if (type == "BEAUTY") {
            return std::make_shared<BeautyService>(params);
        } else if (type == "PLUMBING") {
            return std::make_shared<PlumbingService>(params);
        } else if (type == "ELECTRICAL") {
            return std::make_shared<ElectricalService>(params);
        } else if (type == "CLEANING") {
            return std::make_shared<CleaningService>(params);
        }
        throw std::runtime_error("Unknown service type: " + type);
    }
};

class Service {
protected:
    std::string id;
    std::string name;
    std::string category;
    double basePrice;
    int duration;

public:
    Service(const std::map<std::string, std::string>& params) {
        id = params.at("id");
        name = params.at("name");
        category = params.at("category");
        basePrice = std::stod(params.at("base_price"));
        duration = std::stoi(params.at("duration"));
    }
    
    virtual ~Service() = default;
    virtual double calculatePrice() const = 0;
    virtual std::vector<std::string> getRequirements() const = 0;
};

class BeautyService : public Service {
public:
    BeautyService(const std::map<std::string, std::string>& params) : Service(params) {}
    
    double calculatePrice() const override {
        return basePrice;
    }
    
    std::vector<std::string> getRequirements() const override {
        return {"Beauty kit", "Sanitized tools", "Professional certification"};
    }
};
```

### 5. Command Pattern - Booking Actions

```cpp
class BookingCommand {
public:
    virtual ~BookingCommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
};

class CreateBookingCommand : public BookingCommand {
private:
    std::shared_ptr<Booking> booking;
    std::shared_ptr<BookingService> bookingService;

public:
    CreateBookingCommand(std::shared_ptr<Booking> b, std::shared_ptr<BookingService> bs) 
        : booking(b), bookingService(bs) {}
    
    void execute() override {
        bookingService->createBooking(booking);
    }
    
    void undo() override {
        bookingService->cancelBooking(booking->getId());
    }
};

class AcceptBookingCommand : public BookingCommand {
private:
    std::string bookingId;
    std::string professionalId;
    std::shared_ptr<BookingService> bookingService;

public:
    AcceptBookingCommand(const std::string& bid, const std::string& pid, std::shared_ptr<BookingService> bs) 
        : bookingId(bid), professionalId(pid), bookingService(bs) {}
    
    void execute() override {
        bookingService->acceptBooking(bookingId, professionalId);
    }
    
    void undo() override {
        bookingService->rejectBooking(bookingId, professionalId);
    }
};
```

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
    total_orders INT DEFAULT 0,
    member_since TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    status ENUM('ACTIVE', 'INACTIVE', 'SUSPENDED') DEFAULT 'ACTIVE',
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
);
```

#### 2. Professionals Table
```sql
CREATE TABLE professionals (
    id VARCHAR(36) PRIMARY KEY,
    user_id VARCHAR(36) NOT NULL,
    skills JSON,
    experience_years INT,
    rating DECIMAL(3,2) DEFAULT 0.0,
    total_jobs INT DEFAULT 0,
    earnings DECIMAL(10,2) DEFAULT 0.0,
    verification_status ENUM('PENDING', 'VERIFIED', 'REJECTED') DEFAULT 'PENDING',
    background_check_status ENUM('PENDING', 'PASSED', 'FAILED') DEFAULT 'PENDING',
    documents JSON,
    availability JSON,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (user_id) REFERENCES users(id)
);
```

#### 3. Services Table
```sql
CREATE TABLE services (
    id VARCHAR(36) PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    category_id VARCHAR(36) NOT NULL,
    description TEXT,
    base_price DECIMAL(10,2) NOT NULL,
    duration INT NOT NULL,
    requirements JSON,
    is_active BOOLEAN DEFAULT TRUE,
    popularity_score INT DEFAULT 0,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (category_id) REFERENCES categories(id)
);
```

#### 4. Bookings Table
```sql
CREATE TABLE bookings (
    id VARCHAR(36) PRIMARY KEY,
    customer_id VARCHAR(36) NOT NULL,
    professional_id VARCHAR(36),
    service_id VARCHAR(36) NOT NULL,
    scheduled_time TIMESTAMP NOT NULL,
    actual_time TIMESTAMP,
    status ENUM('PENDING', 'ACCEPTED', 'IN_PROGRESS', 'COMPLETED', 'CANCELLED') DEFAULT 'PENDING',
    amount DECIMAL(10,2) NOT NULL,
    payment_status ENUM('PENDING', 'PAID', 'REFUNDED') DEFAULT 'PENDING',
    rating INT,
    address TEXT NOT NULL,
    special_instructions TEXT,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (customer_id) REFERENCES users(id),
    FOREIGN KEY (professional_id) REFERENCES professionals(id),
    FOREIGN KEY (service_id) REFERENCES services(id)
);
```

#### 5. Payments Table
```sql
CREATE TABLE payments (
    id VARCHAR(36) PRIMARY KEY,
    booking_id VARCHAR(36) NOT NULL,
    amount DECIMAL(10,2) NOT NULL,
    method ENUM('CREDIT_CARD', 'UPI', 'WALLET', 'CASH') NOT NULL,
    status ENUM('PENDING', 'SUCCESS', 'FAILED', 'REFUNDED') DEFAULT 'PENDING',
    transaction_id VARCHAR(100),
    gateway_response JSON,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (booking_id) REFERENCES bookings(id)
);
```

#### 6. Categories Table
```sql
CREATE TABLE categories (
    id VARCHAR(36) PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    description TEXT,
    parent_category_id VARCHAR(36),
    icon_url VARCHAR(255),
    is_active BOOLEAN DEFAULT TRUE,
    display_order INT DEFAULT 0,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    FOREIGN KEY (parent_category_id) REFERENCES categories(id)
);
```

---

## Key Workflows

### 1. Booking Flow

```cpp
class BookingWorkflow {
private:
    std::shared_ptr<BookingService> bookingService;
    std::shared_ptr<NotificationService> notificationService;
    std::shared_ptr<PaymentService> paymentService;

public:
    std::string createBooking(const BookingRequest& request) {
        // 1. Validate request
        if (!validateBookingRequest(request)) {
            throw std::runtime_error("Invalid booking request");
        }
        
        // 2. Check professional availability
        auto availableProfessionals = findAvailableProfessionals(request);
        if (availableProfessionals.empty()) {
            throw std::runtime_error("No professionals available");
        }
        
        // 3. Create booking
        auto booking = std::make_shared<Booking>(request);
        std::string bookingId = bookingService->createBooking(booking);
        
        // 4. Send notifications to professionals
        notificationService->notifyProfessionals(availableProfessionals, booking);
        
        // 5. Send confirmation to customer
        notificationService->notifyCustomer(request.customerId, "BOOKING_CREATED", booking);
        
        return bookingId;
    }
    
    void acceptBooking(const std::string& bookingId, const std::string& professionalId) {
        // 1. Update booking status
        bookingService->acceptBooking(bookingId, professionalId);
        
        // 2. Update professional availability
        bookingService->updateProfessionalAvailability(professionalId, bookingId);
        
        // 3. Send notifications
        auto booking = bookingService->getBooking(bookingId);
        notificationService->notifyCustomer(booking->getCustomerId(), "BOOKING_ACCEPTED", booking);
        
        // 4. Process payment
        paymentService->processPayment(booking);
    }
    
    void completeBooking(const std::string& bookingId) {
        // 1. Update booking status
        bookingService->completeBooking(bookingId);
        
        // 2. Calculate professional earnings
        auto booking = bookingService->getBooking(bookingId);
        bookingService->updateProfessionalEarnings(booking);
        
        // 3. Request rating
        notificationService->requestRating(booking);
        
        // 4. Update customer stats
        bookingService->updateCustomerStats(booking->getCustomerId());
    }
};
```

### 2. Professional Onboarding

```cpp
class ProfessionalOnboardingWorkflow {
private:
    std::shared_ptr<ProfessionalService> professionalService;
    std::shared_ptr<VerificationService> verificationService;
    std::shared_ptr<NotificationService> notificationService;

public:
    std::string onboardProfessional(const ProfessionalOnboardingRequest& request) {
        // 1. Create user account
        auto user = std::make_shared<User>(request.userData);
        std::string userId = professionalService->createUser(user);
        
        // 2. Create professional profile
        auto professional = std::make_shared<Professional>(request.professionalData);
        professional->setUserId(userId);
        std::string professionalId = professionalService->createProfessional(professional);
        
        // 3. Upload documents
        for (const auto& document : request.documents) {
            professionalService->uploadDocument(professionalId, document);
        }
        
        // 4. Initiate background check
        verificationService->initiateBackgroundCheck(professionalId);
        
        // 5. Send welcome notification
        notificationService->notifyProfessional(professionalId, "WELCOME", {});
        
        return professionalId;
    }
    
    void verifyProfessional(const std::string& professionalId) {
        // 1. Update verification status
        professionalService->updateVerificationStatus(professionalId, "VERIFIED");
        
        // 2. Activate professional
        professionalService->activateProfessional(professionalId);
        
        // 3. Send verification notification
        notificationService->notifyProfessional(professionalId, "VERIFIED", {});
        
        // 4. Update availability
        professionalService->updateAvailability(professionalId, true);
    }
};
```

---

## Technical Considerations

### 1. Scalability
- **Microservices architecture** for independent scaling
- **Database sharding** by location/region
- **Caching** for frequently accessed data
- **CDN** for static content delivery

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

## Monitoring & Analytics

### Key Metrics:
```
📊 Booking conversion rate
📈 Professional utilization rate
📈 Customer satisfaction score
📈 Average service completion time
📈 Payment success rate
📈 Professional onboarding time
```

### Real-time Dashboards:
```
🗺️ Active bookings by location
🎯 Professional availability map
📊 Revenue by service category
🎯 Customer support tickets
📊 System performance metrics
```

---

## Conclusion

This comprehensive system design for Urban Company demonstrates:

1. **Scalable microservices architecture**
2. **Proper use of design patterns**
3. **Robust database design**
4. **Comprehensive workflow management**
5. **Production-ready technical considerations**

The design is both interview-ready and production-ready, covering all aspects from entity modeling to technical implementation. 