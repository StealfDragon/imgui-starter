# imgui-starter

Written on MacOS.

I didn't have any questions that I had to go to the instructor about, however, I did have a lot that I had to work out on my own. First of all, it's been a while since I last coded in C++, so I had a lot of reviewing to do. Second, I had to learn dearImGUI. I'm not that experienced with reading documentation, so this also took a while. 

The last thing was that upon viewing the instructor's original code located in application.cpp, I didn't really understand how his functions were supposed to work. He prompted us with calling an info log function and a game log function, despite the fact that info and game aren't in the same log category. Instead, I decided to write logInfo, logWarning, and logError functions, and have an extra parameter in each which would determine whether the log was a regular system log or a game log.