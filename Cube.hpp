#include <optional>
#include <vector>

class Cube{
    private:
        char cube[4][4][4];
    public:
        Cube();

        void clear();
        std::optional<int> result();
        bool play(std::vector<int>);
        void print();
};