# System Design Mind Map & Decision Tree Guide

## Table of Contents
1. [System Design Decision Tree](#system-design-decision-tree)
2. [Entity Relationship Diagram Guide](#entity-relationship-diagram-guide)
3. [Design Pattern Categorization](#design-pattern-categorization)
4. [Step-by-Step Problem Solving](#step-by-step-problem-solving)
5. [Revision Sheet](#revision-sheet)

---

## System Design Decision Tree

### 🎯 **Main Decision Tree**

```
START: System Design Problem
├─ 1. CLARIFY REQUIREMENTS
│   ├─ Functional Requirements?
│   │   ├─ User Management → User/Driver/Admin entities
│   │   ├─ Booking/Ordering → Booking/Order entities
│   │   ├─ Payment → Payment/Transaction entities
│   │   ├─ Communication → Message/Notification entities
│   │   └─ Tracking → Location/Tracking entities
│   │
│   ├─ Non-Functional Requirements?
│   │   ├─ High Scalability → Microservices + Caching
│   │   ├─ Low Latency → CDN + Load Balancing
│   │   ├─ High Availability → Replication + Failover
│   │   ├─ Data Consistency → ACID vs BASE
│   │   └─ Security → Authentication + Encryption
│   │
│   └─ Scale Requirements?
│       ├─ Small Scale (< 1M users) → Monolithic
│       ├─ Medium Scale (1M-10M users) → Microservices
│       └─ Large Scale (> 10M users) → Distributed Systems
│
├─ 2. IDENTIFY ENTITIES
│   ├─ What are the main "things"?
│   │   ├─ Users/People → User, Driver, Admin
│   │   ├─ Services/Products → Service, Product, Item
│   │   ├─ Transactions → Order, Payment, Booking
│   │   ├─ Locations → Address, Coordinates
│   │   └─ Communications → Message, Notification
│   │
│   ├─ What relationships exist?
│   │   ├─ One-to-One → User-Profile
│   │   ├─ One-to-Many → User-Orders
│   │   ├─ Many-to-Many → Users-Groups
│   │   └─ Self-Referential → Employee-Manager
│   │
│   └─ What attributes are needed?
│       ├─ Identifiers → ID, UUID
│       ├─ Basic Info → Name, Email, Phone
│       ├─ Status → Active, Inactive, Pending
│       └─ Timestamps → Created, Updated, Deleted
│
├─ 3. CHOOSE ARCHITECTURE
│   ├─ System Type?
│   │   ├─ Web Application → REST APIs + Frontend
│   │   ├─ Mobile App → API Gateway + Mobile Backend
│   │   ├─ Real-time System → WebSockets + Event Streaming
│   │   ├─ Data Processing → Batch + Stream Processing
│   │   └─ IoT System → Message Queues + Edge Computing
│   │
│   ├─ Architecture Pattern?
│   │   ├─ Monolithic → Simple, Single Codebase
│   │   ├─ Microservices → Scalable, Independent Services
│   │   ├─ Event-Driven → Loose Coupling, Async
│   │   ├─ CQRS → Read/Write Separation
│   │   └─ Serverless → Auto-scaling, Pay-per-use
│   │
│   └─ Data Storage?
│       ├─ Relational → ACID, Complex Queries
│       ├─ NoSQL → Scalable, Flexible Schema
│       ├─ Cache → Fast Access, Temporary Data
│       ├─ Search → Full-text Search, Analytics
│       └─ File Storage → Documents, Media
│
├─ 4. SELECT DESIGN PATTERNS
│   ├─ Behavioral Patterns?
│   │   ├─ Strategy → Multiple algorithms for same task
│   │   ├─ State → Object behavior changes with state
│   │   ├─ Observer → One-to-many notifications
│   │   ├─ Command → Encapsulate requests as objects
│   │   └─ Chain of Responsibility → Sequential processing
│   │
│   ├─ Structural Patterns?
│   │   ├─ Factory → Complex object creation
│   │   ├─ Singleton → Single instance
│   │   ├─ Adapter → Interface compatibility
│   │   ├─ Composite → Tree-like structures
│   │   └─ Proxy → Control access to objects
│   │
│   └─ Creational Patterns?
│       ├─ Builder → Complex object construction
│       ├─ Prototype → Clone existing objects
│       ├─ Abstract Factory → Family of objects
│       └─ Object Pool → Reuse expensive objects
│
├─ 5. DESIGN DATABASE
│   ├─ Database Type?
│   │   ├─ Primary Database → User data, transactions
│   │   ├─ Read Replicas → Analytics, reporting
│   │   ├─ Cache Layer → Session, frequently accessed
│   │   ├─ Search Index → Full-text search
│   │   └─ File Storage → Documents, media files
│   │
│   ├─ Schema Design?
│   │   ├─ Normalized → Reduce redundancy
│   │   ├─ Denormalized → Faster queries
│   │   ├─ Hybrid → Balance of both
│   │   └─ Document → Flexible schema
│   │
│   └─ Scaling Strategy?
│       ├─ Vertical Scaling → Bigger machines
│       ├─ Horizontal Scaling → More machines
│       ├─ Sharding → Split by key
│       └─ Partitioning → Split by range
│
└─ 6. ADDRESS CONCERNS
    ├─ Performance?
    │   ├─ Caching → Redis, CDN
    │   ├─ Load Balancing → Round-robin, Least connections
    │   ├─ Database Optimization → Indexing, Query optimization
    │   └─ Asynchronous Processing → Queues, Background jobs
    │
    ├─ Scalability?
    │   ├─ Auto-scaling → Cloud resources
    │   ├─ Microservices → Independent scaling
    │   ├─ Database Sharding → Distribute load
    │   └─ CDN → Global content distribution
    │
    ├─ Reliability?
    │   ├─ Replication → Data redundancy
    │   ├─ Failover → Automatic recovery
    │   ├─ Circuit Breakers → Prevent cascading failures
    │   └─ Monitoring → Health checks, alerts
    │
    └─ Security?
        ├─ Authentication → JWT, OAuth
        ├─ Authorization → RBAC, ACL
        ├─ Encryption → Data at rest, in transit
        └─ Rate Limiting → Prevent abuse
```

---

## Entity Relationship Diagram Guide

### 📋 **Step-by-Step ERD Creation**

#### **Step 1: Identify Entities (5 minutes)**

**Ask these questions:**
```
❓ What are the main "things" in the system?
❓ What objects do users interact with?
❓ What data needs to be stored?
❓ What are the core business concepts?
```

**Common Entity Categories:**
```
👥 People: User, Customer, Driver, Employee, Admin
🏢 Organizations: Company, Department, Team
📦 Products: Item, Product, Service, Package
💼 Transactions: Order, Payment, Booking, Reservation
📍 Locations: Address, City, Country, Coordinates
📱 Communications: Message, Notification, Email, SMS
📊 Data: Report, Analytics, Log, Event
```

#### **Step 2: Define Attributes (3 minutes)**

**For each entity, identify:**
```
📝 Primary Key: Unique identifier
📝 Basic Info: Name, description, type
📝 Contact Info: Email, phone, address
📝 Status Info: Active, inactive, pending
📝 Timestamps: Created, updated, deleted
📝 Relationships: Foreign keys
```

#### **Step 3: Establish Relationships (5 minutes)**

**Ask these questions:**
```
🔗 How do entities connect to each other?
🔗 What actions link them?
🔗 What are the cardinalities?
🔗 Are relationships optional or mandatory?
```

**Relationship Types:**
```
1:1 (One-to-One): User ↔ Profile
1:N (One-to-Many): User → Orders
N:1 (Many-to-One): Orders → User
M:N (Many-to-Many): Users ↔ Groups
Self-Referential: Employee → Manager
```

#### **Step 4: Draw the ERD (5 minutes)**

**Use these symbols:**
```
Entity: ┌─────────┐
        │ Entity  │
        │ Name    │
        └─────────┘

Relationship: ────○────

Cardinality:
1:1    ────○────○────
1:N    ────○────<────
N:1    ────>────○────
M:N    ────<────>────
```

#### **Step 5: Validate the Design (2 minutes)**

**Check for:**
```
✅ All entities have primary keys
✅ Relationships have proper cardinalities
✅ No circular dependencies
✅ Normalization is appropriate
✅ All requirements are covered
```

---

## Design Pattern Categorization

### 🎮 **Game Systems**

#### **Tic-Tac-Toe**
```
Patterns: Strategy + State
Entities: Board, Player, Game, Move
Relationships: Player → Game, Game → Board
Key Features: Turn-based, Win detection
```

#### **Chess**
```
Patterns: Strategy + Factory + State
Entities: Board, Piece, Player, Move
Relationships: Player → Game, Piece → Board
Key Features: Complex rules, Multiple piece types
```

#### **Snake Game**
```
Patterns: Observer + State + Command
Entities: Snake, Food, Board, Game
Relationships: Snake → Board, Food → Board
Key Features: Real-time, Collision detection
```

### 🏢 **Real-World Systems**

#### **Parking Lot**
```
Patterns: Strategy + Factory + State
Entities: ParkingLot, Vehicle, Spot, Ticket
Relationships: Vehicle → Spot, Spot → ParkingLot
Key Features: Space management, Pricing strategies
```

#### **Elevator System**
```
Patterns: Strategy + Observer + Command
Entities: Elevator, Floor, Button, Request
Relationships: Elevator → Floor, Button → Elevator
Key Features: Scheduling algorithms, Real-time updates
```

#### **Vending Machine**
```
Patterns: State + Strategy + Command
Entities: Machine, Product, Payment, Selection
Relationships: Product → Machine, Payment → Product
Key Features: State management, Payment methods
```

#### **ATM Machine**
```
Patterns: State + Strategy + Command
Entities: ATM, Account, Transaction, Card
Relationships: Card → Account, Transaction → Account
Key Features: Security, Multiple transaction types
```

### 🛒 **E-commerce Systems**

#### **Shopping Cart**
```
Patterns: Strategy + Observer + Factory
Entities: Cart, Product, User, Order
Relationships: User → Cart, Product → Cart
Key Features: Pricing strategies, Inventory management
```

#### **Inventory Management**
```
Patterns: Observer + Strategy + Factory
Entities: Product, Warehouse, Order, Supplier
Relationships: Product → Warehouse, Order → Product
Key Features: Stock tracking, Reorder strategies
```

### 🏠 **Service Platforms**

#### **Uber/Lyft**
```
Patterns: Strategy + State + Observer
Entities: User, Driver, Vehicle, Ride
Relationships: User → Ride, Driver → Ride
Key Features: Real-time tracking, Payment processing
```

#### **Urban Company**
```
Patterns: Strategy + State + Observer
Entities: User, Professional, Service, Booking
Relationships: User → Booking, Professional → Service
Key Features: Service matching, Scheduling
```

### 📁 **Software Systems**

#### **File System**
```
Patterns: Composite + Strategy + State
Entities: File, Directory, User, Permission
Relationships: Directory → File, User → Permission
Key Features: Tree structure, Access control
```

#### **Logging System**
```
Patterns: Strategy + Observer + Chain of Responsibility
Entities: Logger, LogEntry, Handler, Formatter
Relationships: Logger → Handler, Handler → Formatter
Key Features: Multiple outputs, Log levels
```

#### **Chat Application**
```
Patterns: Observer + Mediator + State
Entities: User, Message, ChatRoom, Channel
Relationships: User → Message, Message → ChatRoom
Key Features: Real-time messaging, Group management
```

---

## Step-by-Step Problem Solving

### 🎯 **10-Minute Interview Framework**

#### **Minute 1-2: Clarify Requirements**
```
❓ "Let me understand the requirements first..."
- What are the main features?
- What's the scale (users, transactions per day)?
- Any specific constraints?
- What's the primary use case?
- Any performance requirements?
```

#### **Minute 3: Identify Entities**
```
✅ "The main entities are:"
- [List 4-6 core entities]
- [Explain relationships briefly]
- [Mention key attributes]
```

#### **Minute 4-5: Design Database**
```
✅ "I'll design the database with these tables:"
- [List main tables with key columns]
- [Explain relationships and foreign keys]
- [Mention indexing strategy]
```

#### **Minute 6-7: Choose Architecture**
```
✅ "I'll use [architecture] because:"
- [Explain rationale]
- [List main services/components]
- [Mention scaling strategy]
```

#### **Minute 8: Explain Workflows**
```
✅ "The key workflows are:"
- [Describe 2-3 main workflows]
- [Explain data flow]
- [Mention error handling]
```

#### **Minute 9: Discuss Patterns**
```
✅ "I'll use these design patterns:"
- [List 2-3 relevant patterns]
- [Explain why each is needed]
- [Give brief implementation idea]
```

#### **Minute 10: Address Concerns**
```
✅ "For scalability and performance:"
- [Mention caching strategy]
- [Discuss load balancing]
- [Address security concerns]
- [Consider monitoring]
```

### 🔍 **Pattern Selection Decision Tree**

```
Does the system have multiple ways to do the same thing?
├─ YES → Strategy Pattern
│   Examples: Payment methods, Sorting algorithms, Pricing strategies
│
└─ NO → Continue

Does object behavior change based on internal state?
├─ YES → State Pattern
│   Examples: Order states, Game states, Machine states
│
└─ NO → Continue

Do multiple objects need to be notified of changes?
├─ YES → Observer Pattern
│   Examples: UI updates, Event notifications, Real-time tracking
│
└─ NO → Continue

Is object creation complex or conditional?
├─ YES → Factory Pattern
│   Examples: Different product types, Service creation, Document types
│
└─ NO → Continue

Do you need to handle user requests/actions?
├─ YES → Command Pattern
│   Examples: Button clicks, Menu items, Undo operations
│
└─ NO → Continue

Is there a tree-like structure?
├─ YES → Composite Pattern
│   Examples: File system, UI components, Organization hierarchy
│
└─ NO → Continue

Do you need sequential processing?
├─ YES → Chain of Responsibility
│   Examples: Log levels, Request filters, Validation chains
│
└─ NO → Continue

Do you need to decouple sender from receiver?
├─ YES → Mediator Pattern
│   Examples: Chat rooms, Air traffic control, Event buses
│
└─ NO → Continue
```

---

## Revision Sheet

### 📚 **Quick Reference for Interviews**

#### **Entity Identification Checklist:**
```
✅ What are the main "things" in the system?
✅ What objects do users interact with?
✅ What data needs to be stored?
✅ What are the core business concepts?
✅ What relationships exist between entities?
✅ What attributes are essential for each entity?
```

#### **Database Design Checklist:**
```
✅ Primary keys for all tables
✅ Foreign keys for relationships
✅ Appropriate data types
✅ Indexes for frequent queries
✅ Normalization level appropriate
✅ Constraints and validations
✅ Timestamps for auditing
```

#### **Architecture Selection Checklist:**
```
✅ System type (web, mobile, real-time, etc.)
✅ Scale requirements (users, transactions)
✅ Performance requirements (latency, throughput)
✅ Availability requirements (uptime, failover)
✅ Security requirements (authentication, encryption)
✅ Cost considerations (infrastructure, maintenance)
```

#### **Design Pattern Checklist:**
```
✅ Multiple algorithms for same task → Strategy
✅ Behavior changes with state → State
✅ One-to-many notifications → Observer
✅ Complex object creation → Factory
✅ Handle user requests → Command
✅ Tree-like structure → Composite
✅ Sequential processing → Chain of Responsibility
✅ Decouple components → Mediator
```

#### **Technical Considerations Checklist:**
```
✅ Scalability (horizontal vs vertical)
✅ Performance (caching, optimization)
✅ Reliability (replication, failover)
✅ Security (authentication, authorization)
✅ Monitoring (logging, alerting)
✅ Error handling (retry, circuit breakers)
```

### 🎯 **Common Interview Questions & Answers**

#### **"How would you design [System X]?"**

**Answer Framework:**
```
1. "Let me clarify the requirements first..."
2. "The main entities are [list entities]"
3. "I'll use [architecture] because [rationale]"
4. "The key workflows are [describe workflows]"
5. "I'll use [patterns] for [reasons]"
6. "For scalability, I'll [mention strategies]"
```

#### **"What are the trade-offs of your design?"**

**Answer Framework:**
```
1. "Pros: [list advantages]"
2. "Cons: [list disadvantages]"
3. "Alternatives: [mention other approaches]"
4. "Why this choice: [explain decision]"
```

#### **"How would you scale this system?"**

**Answer Framework:**
```
1. "Horizontal scaling: [add more instances]"
2. "Database scaling: [sharding, read replicas]"
3. "Caching: [Redis, CDN]"
4. "Load balancing: [distribute traffic]"
5. "Microservices: [independent scaling]"
```

### 🚀 **Pro Tips for Success**

#### **Before the Interview:**
- ✅ Practice drawing diagrams quickly
- ✅ Memorize common patterns and their use cases
- ✅ Understand basic database concepts
- ✅ Know common scaling strategies
- ✅ Practice explaining trade-offs

#### **During the Interview:**
- ✅ Start with requirements clarification
- ✅ Draw diagrams while explaining
- ✅ Discuss alternatives and trade-offs
- ✅ Consider edge cases and error handling
- ✅ Mention monitoring and observability

#### **Common Mistakes to Avoid:**
- ❌ Jumping straight to implementation
- ❌ Ignoring non-functional requirements
- ❌ Forgetting about error handling
- ❌ Over-engineering simple problems
- ❌ Not considering security

---

## Conclusion

This comprehensive guide provides:

1. **Systematic decision tree** for any system design problem
2. **Step-by-step ERD creation** process
3. **Design pattern categorization** for common problems
4. **10-minute interview framework** for structured responses
5. **Quick reference sheets** for revision

**Key Success Factors:**
- ✅ **Start with requirements** - don't jump to solutions
- ✅ **Draw diagrams** - visual explanations are powerful
- ✅ **Explain rationale** - show your thinking process
- ✅ **Consider trade-offs** - demonstrate balanced thinking
- ✅ **Address concerns** - show production awareness

**Remember:** The goal is to demonstrate **systematic thinking**, not to use every pattern possible. Focus on **clear communication** and **practical solutions**. 