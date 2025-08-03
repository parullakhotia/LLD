#pragma once

namespace Controller {

class BoardGames {
public:
    virtual ~BoardGames() = default;
    virtual void play() = 0;
};

} // namespace Controller 