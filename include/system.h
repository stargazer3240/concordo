// SPDX-FileCopyrightText: 2023 Fabrício Moura Jácome
//
// SPDX-License-Identifier: MIT

#ifndef SYSTEM_H
#define SYSTEM_H

#include <string_view>
#include <vector>

#include "channels.h"
#include "servers.h"
#include "users.h"

namespace concordo::system {

enum class SystemState { kGuest, kLogged_In, kJoinedServer, kJoinedChannel };

using namespace concordo::user;
using namespace concordo::channel;
using namespace concordo::server;
using std::pair, std::string_view, std::vector, std::tuple;

class System {
 public:
  [[nodiscard]] SystemState getState() const { return current_state_; }
  [[nodiscard]] vector<User> getUserList() const { return user_list_; }

  void create_user(string_view args);
  void user_login(string_view cred);
  bool check_user(EmailAddress a);
  User get_user(EmailAddress a);
  bool check_credentials(string_view cred);
  void disconnect();

  void create_server(string_view name);
  bool check_server(string_view name);
  void change_description(string_view name, string_view desc);
  void change_invite(string_view name, string_view code);
  void list_servers();
  void remove_server(string_view name);
  void leave_server(string_view name);

  void list_participants();

 private:
  using enum SystemState;
  SystemState current_state_{kGuest};
  vector<User> user_list_;
  vector<Server> server_list_;
  User logged_user_;
  Server current_server_;
  Channel current_channel_;
  int last_id_{};
};

void quit();

}  // namespace concordo::system

#endif  // SYSTEM_H
