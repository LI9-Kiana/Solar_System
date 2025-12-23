// @author G. Hemingway, copyright 2025 - All rights reserved
#ifndef PARSER_H
#define PARSER_H

#include <string>

/**
 * Class responsible for loading in custom setup scripts and configuring the
 * Universe appropriately.
 */
class Parser {
public:
    /**
     * Loads the script file and configures the Universe. Consult the
     * assignment README.md for the syntax of the scripts.
     * @param filename - name of the configuration file to parse
     */
    static void loadFile(const std::string& filename);
};

#endif // PARSER_H
