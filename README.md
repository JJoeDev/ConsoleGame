# Console Game

## About this project's origin

Console Game was creates as a school project where we
were instructed to create a project in the Windows Console.

The only requirements was to use Two functions and a single loop.

Whilst most of the programming class is writing code in Microsoft Java (C#) I have developed
stockholm syndrome for C++ and that was the reason for why this code is C++

Due to my previous experience with code, I decided to go all out on this project and try a new
code structure. This structure being inspired / stolen from YouTuber "The Cherno".
The code structure is that the entry point calls an Application class that will then take care of the
rest, It is a structure that allows for the developer to "Pack up" the app and use it again.

Another way I tried to challenge myself was by trying my best to overengineer the application
in ways like creating a custom event manager to ignore specific windows events like CTRL + BREAK
for closing the console. Or by graying out buttons and disabling the resize border.

## What did I learn from this project

As much as I personally dislike Microsoft Windows, the console is quite fun to play with,
It might be a really messy thing to play with because of its infinite amount of deprecated
ways of doing stuff (graying X button vs graying Maximize button), but it is a great way of
training once Google-jitsu to get it to work.

It is also a great way to think about optimizations because the Windows Console is super slow
at writing stuff, so you have to figure out how to make it faster, like not using```system("cls");```

This is something I could see myself doing again in the future, but in Linux just to see if
terminal development is any better on there.
