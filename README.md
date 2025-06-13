# GWin

A Windowing library using libSDL3 as the OS isolation layer.  I am using my GRL (Groot's Runtime Library) to provide data containers, memory management, and other things.  Building this to write my own Cross-Platform, Graphical programs.

This library will be doing everything by hand.  No OS widgets and stuff.  So yes, the resulting UI may not look native.  I'm no longer concerned about that.  Why?  Because programs from Microsoft, Apple, and in the Unix world have given up on their own UI standards.  A lot of programs are these horrible Web UI monstrosities and Web UI doesn't look like natives.  And they certainly don't feel like native apps.  So if the big boys have given up on their own Look And Feel (LAF) standards then 

**Why not QT?  Why not some other lib?**

I gave it serious thought but and I gave it a try.  But I am finding getting into QT is not trivial.  And I struggled with things that should have been blindingly simple.  

I have looked at other UI libraries but they all come up short in my opinion.  Lack of OpenGL widget.  Lack of basic widgets.  Bad feel.  C++.

The C++ aspect of some libraried also deters me.  I like C.  And I get all the arguments for C++ but every C++ code I have seen has taken it too far and make working with it a horrible experience.  Granted, I come from a programming mind set of keeping it *stupidly* simple (KISS).  And a lot of C++ seem to have tossed that aside as far as I am concerned.  Also for hobby programming, I stick with C.  It's my favourite language.

**Why not Dear ImgUi?  Or similar?**

I have only given them a cursory look.  It would probably speed up developement on my actual projects I want to do if I used them.  But looking at the results...  I have to say I am not liking it.  So, yeah, I'm basically reinventing the same wheel others have already done.

**Why not C# or Java?**

For the same reason I am avoiding C++.  I like C.  I've work with C# through my day job and there is no good way to mix 3D with WPF ui.  There is no good way to mix native and managed (it's horrid.)  Java...  They used to have a UI library but I haven't seen much of anything in terms of improvement there.  

## Dependencies

- VS2022
- libSDL v3
- GLEW
- GRL (My project.)

## Building

I have set an environment variable "libSDL" to point to where the libSDL project lives on my system.  You will need to do the same if you want to work with the sln file as is.

I have set an environment variable "libGLEW" to point to where the GLEW project lives on my system.  You will need to do the same if you want to work with the sln file as is.

GRL project is in the same folder where GWin project is found.

I might clean up the building so that it becomes easier for others but at the moment I am coding for myself.
