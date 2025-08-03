# LLD Interview Guide - Design Patterns & System Design

## 🎯 Quick Interview Framework

### 3-Step Pattern Identification Process:
1. **What varies?** → Strategy Pattern
2. **What changes state?** → State Pattern  
3. **What needs to be notified?** → Observer Pattern

---

## 01. Tic-Tac-Toe Game

### 🎯 **Interview Question:** "Design a Tic-Tac-Toe game"

### **Quick Brainstorm (30 seconds):**
```
Entities: Board, Player, Game, Move
Behaviors: Make move, Check win, Switch players
Variations: Human vs AI players
States: InProgress, XWon, OWon, Draw
```

### **Patterns Used:**

#### 1. **Strategy Pattern** 
**Why?** Different ways to make moves
```cpp
// Human makes moves via input
// AI makes moves via algorithm
// Random AI makes random moves
```

#### 2. **State Pattern**
**Why?** Game behavior changes based on state
```cpp
// InProgress: Continue game
// XWon/OWon: Announce winner
// Draw: Announce draw
```

### **Interview Answer Structure:**
```
1. "I'll use Strategy Pattern for player behaviors"
2. "State Pattern for game state management"
3. "Board class handles game logic"
4. "Player class with strategy interface"
5. "Game controller orchestrates everything"
```

---

## 02. Chess Game

### 🎯 **Interview Question:** "Design a Chess game"

### **Quick Brainstorm:**
```
Entities: Board, Pieces, Player, Move
Behaviors: Move validation, Check detection
Variations: Different piece movement rules
States: Check, Checkmate, Stalemate, Normal
```

### **Patterns Used:**

#### 1. **Strategy Pattern**
**Why?** Each piece has different movement rules
```cpp
// Pawn: Forward only, diagonal capture
// Rook: Horizontal/vertical
// Bishop: Diagonal
// Queen: All directions
// King: One square any direction
// Knight: L-shaped movement
```

#### 2. **Factory Pattern**
**Why?** Create different piece types
```cpp
// PieceFactory creates Pawn, Rook, Bishop, etc.
// Each piece has its own movement strategy
```

#### 3. **State Pattern**
**Why?** Game state affects valid moves
```cpp
// Check: Must move to escape check
// Checkmate: Game over
// Stalemate: No valid moves but not in check
```

### **Interview Answer:**
```
1. "Strategy Pattern for piece movement rules"
2. "Factory Pattern for piece creation"
3. "State Pattern for game states (Check/Checkmate)"
4. "Board validates moves based on piece strategy"
5. "Player class manages turn and piece selection"
```

---

## 03. Snake and Food Game

### 🎯 **Interview Question:** "Design a Snake game"

### **Quick Brainstorm:**
```
Entities: Snake, Food, Board, Game
Behaviors: Move snake, Grow, Collision detection
Variations: Different movement directions
States: Playing, GameOver, Paused
```

### **Patterns Used:**

#### 1. **Observer Pattern**
**Why?** Snake needs to know about food location
```cpp
// Snake observes food position
// Game observes collision events
// Score observes food consumption
```

#### 2. **State Pattern**
**Why?** Game behavior changes with state
```cpp
// Playing: Normal movement
// Paused: No movement
// GameOver: Stop everything
```

#### 3. **Command Pattern**
**Why?** Handle different movement commands
```cpp
// Up, Down, Left, Right commands
// Undo last move (if needed)
```

### **Interview Answer:**
```
1. "Observer Pattern for food-snake interaction"
2. "State Pattern for game states"
3. "Command Pattern for movement controls"
4. "Snake as linked list of positions"
5. "Collision detection in game controller"
```

---

## 04. Parking Lot System

### 🎯 **Interview Question:** "Design a Parking Lot system"

### **Quick Brainstorm:**
```
Entities: ParkingLot, Vehicle, Spot, Ticket
Behaviors: Park, Unpark, Calculate fare
Variations: Different vehicle types, pricing strategies
States: Available, Occupied, Reserved
```

### **Patterns Used:**

#### 1. **Strategy Pattern**
**Why?** Different pricing strategies
```cpp
// Hourly rate
// Daily rate
// Monthly rate
// Premium parking
```

#### 2. **Factory Pattern**
**Why?** Create different vehicle types
```cpp
// Car, Motorcycle, Truck, Bus
// Each has different space requirements
```

#### 3. **State Pattern**
**Why?** Spot states affect availability
```cpp
// Available: Can park
// Occupied: Cannot park
// Reserved: Reserved for specific user
```

### **Interview Answer:**
```
1. "Strategy Pattern for pricing strategies"
2. "Factory Pattern for vehicle types"
3. "State Pattern for parking spot states"
4. "Ticket system for tracking"
5. "Multiple levels with different vehicle types"
```

---

## 05. Elevator System

### 🎯 **Interview Question:** "Design an Elevator system"

### **Quick Brainstorm:**
```
Entities: Elevator, Floor, Button, Request
Behaviors: Move, Stop, Open/Close doors
Variations: Different scheduling algorithms
States: Moving, Stopped, Maintenance
```

### **Patterns Used:**

#### 1. **Strategy Pattern**
**Why?** Different scheduling algorithms
```cpp
// First-come-first-served
// Nearest floor first
// Priority-based (VIP floors)
// Load balancing
```

#### 2. **Observer Pattern**
**Why?** Multiple components need updates
```cpp
// Floor buttons observe elevator position
// Display observes current floor
// Maintenance system observes status
```

#### 3. **Command Pattern**
**Why?** Handle button presses
```cpp
// Floor button commands
// Door open/close commands
// Emergency stop command
```

### **Interview Answer:**
```
1. "Strategy Pattern for scheduling algorithms"
2. "Observer Pattern for status updates"
3. "Command Pattern for button presses"
4. "State Pattern for elevator states"
5. "Priority queue for request management"
```

---

## 06. Inventory Management System

### 🎯 **Interview Question:** "Design an Inventory Management system"

### **Quick Brainstorm:**
```
Entities: Product, Warehouse, Order, Supplier
Behaviors: Add/Remove items, Track stock, Reorder
Variations: Different product categories, reorder strategies
States: InStock, LowStock, OutOfStock
```

### **Patterns Used:**

#### 1. **Observer Pattern**
**Why?** Multiple systems need stock updates
```cpp
// Sales system observes stock changes
// Supplier system observes reorder points
// Analytics system observes inventory trends
```

#### 2. **Strategy Pattern**
**Why?** Different reorder strategies
```cpp
// Just-in-time ordering
// Economic order quantity
// Safety stock based
// Seasonal ordering
```

#### 3. **Factory Pattern**
**Why?** Create different product types
```cpp
// Electronics, Clothing, Food, etc.
// Each has different storage requirements
```

### **Interview Answer:**
```
1. "Observer Pattern for stock change notifications"
2. "Strategy Pattern for reorder strategies"
3. "Factory Pattern for product types"
4. "State Pattern for stock levels"
5. "Multiple warehouses with location tracking"
```

---

## 07. Car Rental System

### 🎯 **Interview Question:** "Design a Car Rental system"

### **Quick Brainstorm:**
```
Entities: Car, Customer, Rental, Location
Behaviors: Rent, Return, Calculate cost
Variations: Different car types, pricing models
States: Available, Rented, Maintenance
```

### **Patterns Used:**

#### 1. **Strategy Pattern**
**Why?** Different pricing models
```cpp
// Daily rate
// Weekly rate
// Mileage-based
// Insurance included/excluded
```

#### 2. **State Pattern**
**Why?** Car availability affects operations
```cpp
// Available: Can be rented
// Rented: Cannot be rented
// Maintenance: Cannot be rented
```

#### 3. **Factory Pattern**
**Why?** Create different car types
```cpp
// Economy, Luxury, SUV, Electric
// Each has different pricing and features
```

### **Interview Answer:**
```
1. "Strategy Pattern for pricing models"
2. "State Pattern for car availability"
3. "Factory Pattern for car types"
4. "Location-based availability"
5. "Reservation system with time slots"
```

---

## 08. Vending Machine

### 🎯 **Interview Question:** "Design a Vending Machine"

### **Quick Brainstorm:**
```
Entities: Machine, Product, Payment, Selection
Behaviors: Accept payment, Dispense, Calculate change
Variations: Different payment methods, product types
States: Idle, Payment, Dispensing, Maintenance
```

### **Patterns Used:**

#### 1. **State Pattern**
**Why?** Machine behavior changes with state
```cpp
// Idle: Accept selection
// Payment: Accept money
// Dispensing: Dispense product
// Maintenance: Service mode
```

#### 2. **Strategy Pattern**
**Why?** Different payment methods
```cpp
// Cash payment
// Card payment
// Mobile payment
// Cryptocurrency
```

#### 3. **Command Pattern**
**Why?** Handle button presses
```cpp
// Product selection commands
// Payment commands
// Cancel command
```

### **Interview Answer:**
```
1. "State Pattern for machine states"
2. "Strategy Pattern for payment methods"
3. "Command Pattern for button interactions"
4. "Inventory tracking for products"
5. "Change calculation system"
```

---

## 09. File System

### 🎯 **Interview Question:** "Design a File System"

### **Quick Brainstorm:**
```
Entities: File, Directory, FileSystem, User
Behaviors: Create, Read, Write, Delete
Variations: Different file types, access permissions
States: Open, Closed, Corrupted
```

### **Patterns Used:**

#### 1. **Composite Pattern**
**Why?** Files and directories form tree structure
```cpp
// Directory contains files and subdirectories
// Uniform interface for both
```

#### 2. **Strategy Pattern**
**Why?** Different file operations
```cpp
// Text file operations
// Binary file operations
// Compressed file operations
```

#### 3. **State Pattern**
**Why?** File states affect operations
```cpp
// Open: Can read/write
// Closed: Cannot access
// Corrupted: Cannot access
```

### **Interview Answer:**
```
1. "Composite Pattern for file/directory tree"
2. "Strategy Pattern for file operations"
3. "State Pattern for file states"
4. "Permission system for access control"
5. "Hierarchical namespace structure"
```

---

## 10. Logging System

### 🎯 **Interview Question:** "Design a Logging System"

### **Quick Brainstorm:**
```
Entities: Logger, LogEntry, Handler, Formatter
Behaviors: Write logs, Format, Route
Variations: Different log levels, output destinations
States: Active, Paused, Error
```

### **Patterns Used:**

#### 1. **Strategy Pattern**
**Why?** Different output strategies
```cpp
// Console output
// File output
// Database output
// Network output
```

#### 2. **Observer Pattern**
**Why?** Multiple handlers for same log
```cpp
// File handler observes log events
// Console handler observes log events
// Email handler for critical errors
```

#### 3. **Chain of Responsibility**
**Why?** Filter logs by level
```cpp
// Debug → Info → Warning → Error → Critical
// Each level decides to pass or handle
```

### **Interview Answer:**
```
1. "Strategy Pattern for output destinations"
2. "Observer Pattern for multiple handlers"
3. "Chain of Responsibility for log levels"
4. "Async logging for performance"
5. "Configurable log formats"
```

---

## 11. Splitwise (Expense Sharing)

### 🎯 **Interview Question:** "Design a Splitwise-like expense sharing app"

### **Quick Brainstorm:**
```
Entities: User, Expense, Group, Settlement
Behaviors: Add expense, Split, Calculate balances
Variations: Different split strategies, payment methods
States: Pending, Settled, Disputed
```

### **Patterns Used:**

#### 1. **Strategy Pattern**
**Why?** Different split strategies
```cpp
// Equal split
// Percentage split
// Custom amounts
// Proportional to income
```

#### 2. **Observer Pattern**
**Why?** Users need balance updates
```cpp
// Users observe expense additions
// Group observes member changes
// Notifications for settlements
```

#### 3. **State Pattern**
**Why?** Expense states affect operations
```cpp
// Pending: Can be modified
// Settled: Cannot be modified
// Disputed: Needs resolution
```

### **Interview Answer:**
```
1. "Strategy Pattern for split strategies"
2. "Observer Pattern for balance updates"
3. "State Pattern for expense states"
4. "Graph algorithm for debt optimization"
5. "Group management with permissions"
```

---

## 12. ATM Machine

### 🎯 **Interview Question:** "Design an ATM Machine"

### **Quick Brainstorm:**
```
Entities: ATM, Account, Transaction, Card
Behaviors: Authenticate, Withdraw, Deposit, Transfer
Variations: Different transaction types, security methods
States: Idle, Authenticating, Processing, Error
```

### **Patterns Used:**

#### 1. **State Pattern**
**Why?** ATM behavior changes with state
```cpp
// Idle: Accept card
// Authenticating: Verify PIN
// Processing: Execute transaction
// Error: Handle failures
```

#### 2. **Strategy Pattern**
**Why?** Different transaction types
```cpp
// Withdrawal strategy
// Deposit strategy
// Transfer strategy
// Balance inquiry
```

#### 3. **Command Pattern**
**Why?** Handle user requests
```cpp
// Withdraw command
// Deposit command
// Transfer command
// Cancel command
```

### **Interview Answer:**
```
1. "State Pattern for ATM states"
2. "Strategy Pattern for transaction types"
3. "Command Pattern for user requests"
4. "Security layer for authentication"
5. "Transaction logging and audit trail"
```

---

## 🎯 **Quick Interview Tips**

### **Before Starting:**
1. **Clarify requirements** (2 minutes)
2. **Identify entities** (1 minute)
3. **Spot variations** (1 minute)
4. **Choose patterns** (1 minute)

### **Pattern Selection Rules:**
```
Multiple ways to do same thing → Strategy
Behavior changes with state → State
One-to-many notifications → Observer
Complex object creation → Factory
Tree-like structure → Composite
Sequential processing → Chain of Responsibility
```

### **Common Interview Mistakes:**
- ❌ Over-engineering simple problems
- ❌ Not considering scalability
- ❌ Ignoring edge cases
- ❌ Not explaining trade-offs

### **Always Mention:**
- ✅ Error handling
- ✅ Thread safety (if applicable)
- ✅ Performance considerations
- ✅ Scalability aspects
- ✅ Security concerns

This guide provides a systematic approach to tackle any LLD interview question with confidence! 