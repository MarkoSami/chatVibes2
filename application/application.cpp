
#include "application/application.h"
#include "logic/user.h"
#include "logic/contact.h"
#include "logic/story.h"

std::list<User*> Application::users = {};

std::unordered_map<std::string, std::list<Story*>> Application::stories ;

User* Application::loggedUser = nullptr;
Story* Application::currentStory = nullptr ;
std::list<Story*> Application::currentStoryList ;
Conversation *Application::currentConversation;

Application::Application()
{

}






// User("starterUser","starterUser","starterUser","fdsfs","dsfsdf","dsff",true)
