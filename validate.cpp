#include <algorithm>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

using Coord = std::tuple<size_t, size_t, size_t>;

class Maze {
public:
    explicit Maze(std::istream &in) : height_(0), width_(0), depth_(0) {
        in >> height_;
        if (!in) {
            throw std::runtime_error("can't read the height of the maze");
        }

        in >> width_;
        if (!in) {
            throw std::runtime_error("can't read the width of the maze");
        }

        in >> depth_;
        if (!in) {
            throw std::runtime_error("can't read the depth of the maze");
        }

        maze.reserve(height_ * width_ * depth_);

        for (size_t d = 0; d < depth_; ++d) {
            for (size_t r = 0; r < height_; ++r) {
                for (size_t c = 0; c < width_; ++c) {
                    int space;
                    in >> space;
                    if (!in) {
                        std::stringstream error_message;
                        error_message << "can't read the maze space at " << r << ' ' << c << ' ' << d;
                        throw std::runtime_error(error_message.str());
                    }
                    if (space != 0 && space != 1) {
                        std::stringstream error_message;
                        error_message << "got invalid space at " << r << ' ' << c << ' ' << d
                                      << ": each space can only be 0 or 1, but this space is " << space;
                        throw std::runtime_error(error_message.str());
                    }
                    maze.push_back(space);
                }
            }
        }
    }

    const int &operator[](const Coord &coord) const {
        return maze[index(coord)];
    }

    [[nodiscard]] size_t height() const {
        return height_;
    }

    [[nodiscard]] size_t width() const {
        return width_;
    }

    [[nodiscard]] size_t depth() const {
        return depth_;
    }

private:
    size_t height_;
    size_t width_;
    size_t depth_;
    std::vector<int> maze;

    [[nodiscard]] constexpr size_t index(const Coord &point) const {
        return std::get<2>(point) * height_ * width_ + std::get<0>(point) * width_ + std::get<1>(point);
    }
};

void read_coord(std::istream &in, size_t &row, size_t &column, size_t &depth) {
    in >> row;
    if (!in) {
        throw std::runtime_error("could not read the row component of the coordinate");
    }

    in >> column;
    if (!in) {
        throw std::runtime_error("could not read the column component of the coordinate");
    }

    in >> depth;
    if (!in) {
        throw std::runtime_error("could not read the depth component of the coordinate");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " [MAZE FILE] [OUTPUT FILE]" << std::endl;
        return 1;
    }

    std::ifstream maze_input(argv[1]);
    if (!maze_input) {
        std::cerr << "Failed to open " << argv[1] << " for reading." << std::endl;
        return 1;
    }
    std::optional<Maze> maybe_maze = {};
    try {
        maybe_maze = Maze(maze_input);
    } catch (const std::runtime_error &e) {
        std::cerr << "Failed to read " << argv[1] << " as a maze: " << e.what() << std::endl;
        return 1;
    }
    Maze maze = *maybe_maze;

    std::ifstream solution(argv[2]);
    if (!solution) {
        std::cerr << "Failed to open " << argv[2] << " for reading." << std::endl;
        return 1;
    }

    std::string line;
    std::getline(solution, line);
    if (line == "NO SOLUTION") {
        std::cout << "The output file says that the given maze has no solution. This program can check\n"
                     "that a given solution is valid, but it can't verify that there really is no\n"
                     "solution to the given maze." << std::endl;
        return 0;
    } else if (line != "SOLUTION") {
        std::cerr << R"([Line 1]: the only valid options for the first line are "SOLUTION" and "NO SOLUTION".)"
                  << std::endl;
        return 1;
    }

    size_t row;
    size_t column;
    size_t depth;
    std::stringstream line_stream;
    int line_number = 2;

    std::getline(solution, line);
    line_stream.str(line);

    try {
        read_coord(line_stream, row, column, depth);
    } catch (const std::runtime_error &e) {
        std::cerr << "[Line " << line_number << "]: " << e.what() << std::endl;
        return 1;
    }

    if (row != 0 || column != 0 || depth != 0) {
        std::cerr << "[Line " << line_number << "]: the solution starts at " << row << ' ' << column << ' ' << depth
                  << ", but all solutions should start at 0 0 0." << std::endl;
        return 1;
    }

    while (std::getline(solution, line) && !line.empty()) {
        line_stream.clear();
        line_stream.str(line);
        line_number += 1;

        size_t prev_row = row;
        size_t prev_column = column;
        size_t prev_depth = depth;

        try {
            read_coord(line_stream, row, column, depth);
        } catch (const std::runtime_error &e) {
            std::cerr << "[Line " << line_number << "]: " << e.what() << std::endl;
            return 1;
        }

        if (row >= maze.height() || column >= maze.width() || depth >= maze.depth()) {
            std::cerr << "[Line " << line_number << "]: the solution attempts to move to "
                      << row << ' ' << column << ' ' << depth
                      << ", but that space is out of bounds (the maze is " << maze.height() << " spaces tall, "
                      << maze.width() << " spaces wide, and " << maze.depth() << " spaces deep)." << std::endl;
            return 1;
        }

        if (maze[{row, column, depth}] != 1) {
            std::cerr << "[Line " << line_number << "]: the solution attempts to move to " << row << ' '
                      << column << ' ' << depth
                      << ", but that space is blocked." << std::endl;
            return 1;
        }

        using signed_size_t = std::make_signed_t<size_t>;
        signed_size_t total_moves = std::abs((signed_size_t) (row - prev_row)) +
                                    std::abs((signed_size_t) (column - prev_column)) +
                                    std::abs((signed_size_t) (depth - prev_depth));
        if (total_moves > 1) {
            std::cerr << "[Line " << line_number << "]: the solution attempts to move from "
                      << prev_row << ' ' << prev_column << ' ' << prev_depth << " to "
                      << row << ' ' << column << ' ' << depth << ", which is too far for one move." << std::endl;
            return 1;
        }
    }

    if (row + 1 != maze.height() || column + 1 != maze.width() || depth + 1 != maze.depth()) {
        std::cerr << "[Line " << line_number << "]: the solution ended at " << row << ' ' << column << ' ' << depth
                  << ", but it should have ended at the end, which is at "
                  << maze.height() - 1 << ' ' << maze.width() - 1 << ' ' << maze.depth() - 1
                  << '.' << std::endl;
        return 1;
    }

    std::cout << "That is a valid path through the maze!" << std::endl;
    return 0;
}
