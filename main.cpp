#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Abstract Pet class
class Pet {
public:
    virtual void makeSound() const = 0;
    virtual int getValue() const = 0; // New method to get pet value
    virtual ~Pet() {}
};

// Derived Pet classes
class Dog : public Pet {
public:
    void makeSound() const override {
        std::cout << "Woof!" << std::endl;
    }
    int getValue() const override { return 1; } // Dog has a value of 1
};

class Cat : public Pet {
public:
    void makeSound() const override {
        std::cout << "Meow!" << std::endl;
    }
    int getValue() const override { return 2; } // Cat has a value of 2
};

// Character class
class Character {
public:
    Character(int x, int y) : x(x), y(y) {
        if (rand() % 2 == 0) {
            pet = new Dog();
        } else {
            pet = new Cat();
        }
    }
    
    ~Character() {
        delete pet;
    }
    
    void move(char direction) {
        switch (direction) {
            case 'w':
            case 'W':
                if (y < 9) y++;
                break;
            case 's':
            case 'S':
                if (y > 0) y--;
                break;
            case 'a':
            case 'A':
                if (x > 0) x--;
                break;
            case 'd':
            case 'D':
                if (x < 9) x++;
                break;
        }
    }
    
    int getX() const { return x; }
    int getY() const { return y; }
    Pet* getPet() const { return pet; } // Getter for pet
    
private:
    int x, y;
    Pet* pet;
};

// Board class
class Board {
public:
    Board() {
        grid = std::vector<std::vector<char>>(10, std::vector<char>(10, ' '));
    }
    
    void placeCharacter(const Character& character) {
        grid[character.getY()][character.getX()] = '.';
    }
    
    void clear() {
        for (auto& row : grid) {
            std::fill(row.begin(), row.end(), ' ');
        }
    }
    
    void render(SDL_Renderer* renderer) const {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
        
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (grid[i][j] == '.') {
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                } else {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                }
                SDL_Rect rect = { j * 50, (9 - i) * 50, 50, 50 };
                SDL_RenderFillRect(renderer, &rect);
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                SDL_RenderDrawRect(renderer, &rect);
            }
        }
        
        SDL_RenderPresent(renderer);
    }
    
private:
    std::vector<std::vector<char>> grid;
};

// Function to handle battle between characters
void handleBattle(Character& player, Character& bot) {
    // Get pets and their values
    Pet* playerPet = player.getPet();
    Pet* botPet = bot.getPet();
    int playerValue = playerPet->getValue();
    int botValue = botPet->getValue();
    
    // Compare values to determine battle result
    if (playerValue == botValue) {
        std::cout << "Tie!" << std::endl;
    } else if (playerValue > botValue) {
        std::cout << "Player wins!" << std::endl;
    } else {
        std::cout << "Bot wins!" << std::endl;
    }
}

// Main function
int main() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    
    SDL_Window* window = SDL_CreateWindow("Zoot Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }
    
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Board board;
    Character player(0, 0); // Player character
    Character bot(9, 9);    // Bot character starting at the opposite corner
    
    bool running = true;
    SDL_Event event;
    
    while (running) {
        board.clear();
        board.placeCharacter(player);
        board.placeCharacter(bot);
        board.render(renderer);
        
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    // case SDLK_w:
                    // case SDLK_UP:
                    //     player.move('w');
                    //     break;
                    // case SDLK_s:
                    // case SDLK_DOWN:
                    //     player.move('s');
                    //     break;
                    // case SDLK_a:
                    // case SDLK_LEFT:
                    //     player.move('a');
                    //     break;
                    // case SDLK_d:
                    // case SDLK_RIGHT:
                    //     player.move('d');
                    //     break;
                    case SDLK_q:
                        running = false;
                        break;
                }
            }
        }
        
        // Bot makes a random move
        char directions[] = {'w', 's', 'a', 'd'};
        player.move(directions[rand() % 4]);
        bot.move(directions[rand() % 4]);
        
        // Check for collision and handle battle
        // if (player.getX() == bot.getX() && player.getY() == bot.getY()) {
        //     handleBattle(player, bot);
        // }
        if (abs(player.getX() - bot.getX()) <= 2 && abs(player.getY() - bot.getY()) <= 2) {
            handleBattle(player, bot);
        }
        
        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}