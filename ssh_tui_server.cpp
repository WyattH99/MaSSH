#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/screen/string.hpp>

#include <memory>  // for allocator, __shared_ptr_access
#include <string>  // for char_traits, operator+, string, basic_string
 
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Input, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, separator, Element, operator|, vbox, border
#include "ftxui/util/ref.hpp"  // for Ref


int main() {
  using namespace ftxui;

  /*
  // Screen Example
  std::cout << "\n################  SCREEN EXAMPLE  ################\n";
  auto screen = Screen::Create(Dimension::Fixed(32), Dimension::Fixed(10));

  auto& pixel = screen.PixelAt(16,5);
  pixel.character = U'A';
  pixel.bold = true;
  pixel.foreground_color = Color::Blue;

  std::cout << screen.ToString() << "\n";

  // DOM Example
  std::cout << "\n################  DOM EXAMPLE  ################\n";

  // Define the document
  Element document = vbox({ text("The Window") | bold | color(Color::Blue),
                            gauge(0.5),
                            text("The Footer")
  });

  // Add a border, by calling the 'ftxui::border' decorator function.
  document = border(document);

  // Add another border, using the pipe operator.
  document = document | border;

  // Add another border, using the |= operator
  document |= border;



  std::cout << "\n################  COMPONENT EXAMPLE  ################\n";

  // The data
  std::string target = "This is the sentence to write";
  std::string user_input;

  // The basic input components
  Component input_user_text = Input(&user_input, "User Input: ");

  // The component tree:
  auto component = Container::Vertical({
                                       input_user_text,
  });

  // Tweak how the component tree is rendered

  auto component_screen = ScreenInteractive::TerminalOutput();
  component_screen.Loop(component);
  */
    // The data:
  std::string first_name;
  std::string last_name;
  std::string password;
  std::string phoneNumber;
 
  // The basic input components:
  Component input_first_name = Input(&first_name, "first name");
  Component input_last_name = Input(&last_name, "last name");
 
  // The password input component:
  InputOption password_option;
  password_option.password = true;
  Component input_password = Input(&password, "password", password_option);
 
  // The phone number input component:
  // We are using `CatchEvent` to filter out non-digit characters.
  Component input_phone_number = Input(&phoneNumber, "phone number");
  input_phone_number |= CatchEvent([&](Event event) {
    return event.is_character() && !std::isdigit(event.character()[0]);
  });
  input_phone_number |= CatchEvent([&](Event event) {
    return event.is_character() && phoneNumber.size() > 10;
  });
 
  // The component tree:
  auto component = Container::Vertical({
      input_first_name,
      input_last_name,
      input_password,
      input_phone_number,
  });
 
  // Tweak how the component tree is rendered:
  auto renderer = Renderer(component, [&] {
    return vbox({
               hbox(text(" First name : "), input_first_name->Render()),
               hbox(text(" Last name  : "), input_last_name->Render()),
               hbox(text(" Password   : "), input_password->Render()),
               hbox(text(" Phone num  : "), input_phone_number->Render()),
               separator(),
               text("Hello " + first_name + " " + last_name),
               text("Your password is " + password),
               text("Your phone number is " + phoneNumber),
           }) |
           border;
  });
 
  auto screen = ScreenInteractive::TerminalOutput();
  screen.Loop(renderer);

/*
  auto summary = [&] {
    auto content = vbox({
        hbox({text(L"- done:   "), text(L"3") | bold}) | color(Color::Green),
        hbox({text(L"- active: "), text(L"2") | bold}) | color(Color::RedLight),
        hbox({text(L"- queue:  "), text(L"9") | bold}) | color(Color::Red),
    });
    return window(text(L" Summary "), content);
  };

  auto document =  //
      vbox({
          hbox({
              summary(),
              summary(),
              summary() | flex,
          }),
          summary(),
          summary(),
      });

  // Limit the size of the document to 80 char.
  document = document | size(WIDTH, LESS_THAN, 80);

  auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
  Render(screen, document);

  std::cout << screen.ToString() << '\0' << std::endl;
*/

  return EXIT_SUCCESS;
}
