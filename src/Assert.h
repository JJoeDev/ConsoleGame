#ifndef ASSERT_H
#define ASSERT_H

#include <string>
#include <fstream>

namespace Utils{
    static void FATAL_ASSERT(bool condition, const std::string& msg){
        if(!condition){
            std::ofstream logFile("ConsoleGame.log", std::ios_base::out | std::ios_base::app);
            logFile << msg << '\n';
            logFile.close();
            exit(-1);
        }
    }
}

#endif //ASSERT_H
