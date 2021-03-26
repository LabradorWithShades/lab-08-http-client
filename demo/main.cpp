// Copyright 2020 LabradorWithShades
// 70892548+LabradorWithShades@users.noreply.github.com

#include <auto_complete_client.hpp>

#include <iomanip>
#include <iostream>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Error! Usage: " << std::endl
              << "     demo <hostname> <port>" << std::endl;
    return 1;
  }
  AutoCompleteClient client(argv[1], argv[2]);

  std::string username{};
  std::cout << "Please, enter username: ";
  std::cin >> username;

  std::cout << "To quit application, type \'suggestions.stop\'" << std::endl;

  std::string input{};
  while (input != "suggestions.stop") {
    std::cout << "[ " << username << " ]: ";
    std::cin >> input;

    std::cout << "Server response:" << std::endl;
    std::cout << std::setw(4) << client.sendRequest(username, input);
    std::cout << std::endl << std::endl;
  }

  return 0;
}