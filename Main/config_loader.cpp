#include "config_loader.h"
#include <fstream>
#include <iostream>
#include <string>

namespace app::config
{
    std::vector<int> ConfigLoader::load_game_ids(const std::filesystem::path& config_path)
    {
        std::vector<int> ids{};
        std::ifstream file(config_path);

        if (!file.is_open())
        {
            return ids;
        }

        std::string line{};
        while (std::getline(file, line))
        {
            // Remove comments
            if (size_t comment_pos{ line.find('#') }; comment_pos != std::string::npos)
            {
                line = line.substr(0, comment_pos);
            }

            // Trim whitespace (simple implementation)
            const auto start{ line.find_first_not_of(" \t") };
            if (start == std::string::npos)
            {
                continue;
            }
            const auto end{ line.find_last_not_of(" \t") };
            line = line.substr(start, end - start + 1);

            if (!line.empty())
            {
                try
                {
                    const int id{ std::stoi(line) };
                    if (id > 0)
                    {
                        ids.push_back(id);
                    }
                }
                catch (...)
                {
                    // Ignore parsing errors
                }
            }
        }
        return ids;
    }
}
