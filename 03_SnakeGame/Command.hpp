#pragma once

// Command interface - Strategy pattern for different commands
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};
