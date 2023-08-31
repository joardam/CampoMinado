#include <vector>
#include <SFML/Graphics.hpp>
#include <time.h>
#include "GameFunctions.h"
#include <iostream>


int main() {
    int choice;
    int lamp = false;
    int matrixSize = 14;
    int matrixArea = (matrixSize) * (matrixSize);
    int inGameMatrix = matrixSize + 2;
    float difficulty = float(matrixArea*0.15f);

    while (true) {
        std::cout << "Menu:" << std::endl;
        std::cout << "1. Jogar" << std::endl;
        std::cout << "2. Personalizar" << std::endl;
        std::cout << "3. Sair" << std::endl;
        std::cout << "Escolha uma opção: ";

        if (!(std::cin >> choice)) {
            std::cout << "Entrada inválida. Por favor, insira um número." << std::endl;
            
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue; 
        }

        switch (choice) {
        case 1:
            std::cout << "Iniciando o jogo..." << std::endl;
            startGame(int(difficulty), lamp, inGameMatrix);
            break;
        case 2:
            std::cout << "Ativar Power up lampada? (1 - [Sim] , 2 - [Não]): ";
            int lampChoice;
            while (!(std::cin >> lampChoice) || (lampChoice != 1 && lampChoice != 2)) {
                std::cout << "Escolha inválida. Digite 1 para sim ou 2 para não: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
            lamp = (lampChoice == 1);
            

            std::cout << "Escolha o tamanho da matriz (1-30): ";
            while (!(std::cin >> matrixSize) || matrixSize < 9 || matrixSize > 30) {
                std::cout << "Tamanho inválido. Escolha novamente: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
    
            matrixArea = (matrixSize) * (matrixSize);
            inGameMatrix = matrixSize + 2;




            std::cout << "Escolha a dificuldade (1 - [Fácil] / 2 - [Médio] / 3 - [Difícil]): ";
            int difficultyChoice;
            while (!(std::cin >> difficultyChoice) || (difficultyChoice < 1 || difficultyChoice > 3)) {
                std::cout << "Dificuldade inválida. Escolha novamente: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            if (difficultyChoice == 1) {
                difficulty = 0.15f;
            }
            else if (difficultyChoice == 2) {
                difficulty = 0.20f;
            }
            else if (difficultyChoice == 3) {
                difficulty = 0.25f;
            }

            difficulty = float(matrixArea * difficulty);

            

            std::cout << "Configurações personalizadas salvas." << std::endl;
            break;
        case 3:
            std::cout << "Saindo do programa..." << std::endl;
            return 0;
        default:
            std::cout << "Opção inválida. Escolha novamente." << std::endl;
            break;
        }
    }


	return 0;
}
