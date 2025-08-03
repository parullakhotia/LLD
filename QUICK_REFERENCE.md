# 🚀 LLD Interview Quick Reference

## 🎯 **5-Minute Interview Framework**

### **Step 1: Clarify Requirements (1 min)**
```
- What are the main features?
- What are the constraints?
- What's the scale?
- Any specific requirements?
```

### **Step 2: Identify Entities (1 min)**
```
- What are the main objects?
- How do they interact?
- What are their relationships?
```

### **Step 3: Spot Variations (1 min)**
```
- What behaviors vary?
- What changes frequently?
- What has multiple implementations?
```

### **Step 4: Choose Patterns (1 min)**
```
- Strategy: Multiple ways to do same thing
- State: Behavior changes with state
- Observer: One-to-many notifications
- Factory: Complex object creation
- Command: Handle requests/actions
```

### **Step 5: Design Classes (1 min)**
```
- Core classes
- Interface definitions
- Relationships
- Key methods
```

---

## 🔍 **Pattern Identification Cheat Sheet**

| **Look For** | **Pattern** | **Example** |
|--------------|-------------|-------------|
| Multiple algorithms for same task | **Strategy** | Payment methods, Sorting algorithms |
| Object behavior changes with state | **State** | Game states, Order states |
| One-to-many notifications | **Observer** | UI updates, Event handling |
| Complex object creation | **Factory** | Different product types |
| Handle user requests/actions | **Command** | Button presses, Menu items |
| Tree-like structure | **Composite** | File system, UI components |
| Sequential processing | **Chain of Responsibility** | Log levels, Request filters |
| Decouple sender from receiver | **Mediator** | Chat rooms, Air traffic control |

---

## 🎮 **Common LLD Problems & Patterns**

### **Game Systems**
```
Tic-Tac-Toe: Strategy + State
Chess: Strategy + Factory + State
Snake: Observer + State + Command
```

### **Real-World Systems**
```
Parking Lot: Strategy + Factory + State
Elevator: Strategy + Observer + Command
Vending Machine: State + Strategy + Command
ATM: State + Strategy + Command
```

### **Software Systems**
```
File System: Composite + Strategy + State
Logging: Strategy + Observer + Chain of Responsibility
Inventory: Observer + Strategy + Factory
```

---

## 💡 **Interview Answer Templates**

### **Opening Statement:**
```
"I'll design this system using [Pattern1] for [reason1], 
[Pattern2] for [reason2], and [Pattern3] for [reason3]."
```

### **Class Structure:**
```
1. Core Entity Classes
2. Strategy/State Interfaces
3. Concrete Implementations
4. Controller/Manager Classes
5. Utility Classes
```

### **Key Methods:**
```
- Creation methods (Factory)
- Behavior methods (Strategy)
- State transition methods (State)
- Notification methods (Observer)
- Request handling methods (Command)
```

---

## ⚡ **Quick Pattern Examples**

### **Strategy Pattern:**
```cpp
// Payment strategies
class PaymentStrategy {
    virtual void pay(double amount) = 0;
};

class CreditCardStrategy : public PaymentStrategy {
    void pay(double amount) override { /* ... */ }
};

class PayPalStrategy : public PaymentStrategy {
    void pay(double amount) override { /* ... */ }
};
```

### **State Pattern:**
```cpp
// Order states
class OrderState {
    virtual void process() = 0;
    virtual void cancel() = 0;
};

class PendingState : public OrderState {
    void process() override { /* ... */ }
    void cancel() override { /* ... */ }
};
```

### **Observer Pattern:**
```cpp
// Stock price updates
class Observer {
    virtual void update(double price) = 0;
};

class StockDisplay : public Observer {
    void update(double price) override { /* ... */ }
};
```

---

## 🎯 **Interview Success Checklist**

### **Before Answering:**
- ✅ Clarified requirements
- ✅ Identified main entities
- ✅ Spotted variations
- ✅ Chose appropriate patterns

### **During Answer:**
- ✅ Explained pattern choices
- ✅ Showed class relationships
- ✅ Mentioned key methods
- ✅ Discussed trade-offs

### **Always Mention:**
- ✅ Error handling
- ✅ Thread safety
- ✅ Performance considerations
- ✅ Scalability
- ✅ Security (if applicable)

---

## 🚨 **Common Mistakes to Avoid**

| **Mistake** | **Why It's Bad** | **Better Approach** |
|-------------|------------------|-------------------|
| Over-engineering | Adds unnecessary complexity | Start simple, add patterns when needed |
| Not considering scale | Design won't work in practice | Think about real-world usage |
| Ignoring edge cases | System will fail | Consider error scenarios |
| Not explaining trade-offs | Shows lack of depth | Discuss pros/cons of choices |

---

## 🎪 **Quick Pattern Decision Tree**

```
Does the system have multiple ways to do the same thing?
├─ YES → Strategy Pattern
└─ NO → Continue

Does object behavior change based on internal state?
├─ YES → State Pattern
└─ NO → Continue

Do multiple objects need to be notified of changes?
├─ YES → Observer Pattern
└─ NO → Continue

Is object creation complex or conditional?
├─ YES → Factory Pattern
└─ NO → Continue

Do you need to handle user requests/actions?
├─ YES → Command Pattern
└─ NO → Continue

Is there a tree-like structure?
├─ YES → Composite Pattern
└─ NO → Continue
```

---

## 🏆 **Pro Tips**

1. **Start with the problem, not the pattern**
2. **Explain your reasoning, not just the solution**
3. **Consider real-world constraints**
4. **Think about maintenance and extensibility**
5. **Always have a backup plan**

---

*Remember: The goal is to show systematic thinking, not to use every pattern possible!* 