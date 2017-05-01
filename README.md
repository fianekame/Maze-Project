## Simple Maze Generator

A Simple Program That Makes Random Maze Using Opengl Api With C++ Language. This Program Was Made On My Current Computer Graphics Courses Finish In 2017. To Create A Maze Of Random Cell Size 8 X 8 (Still Static) I Am Using The Kruskal Algorithmhow It Works By Creating A Path Between Cells. For The Current Implementation Of Kruskal On This Program Still Uses An Array To Store The Data Cell  

**-Program ScreenShoot**  

![Alt text](https://raw.githubusercontent.com/fianekame/Maze-Project/master/Screenshot%20from%202017-04-24%2015%3A31%3A45.png "Image")  

### - Introduction

- [About Kruskal Algorithm](https://www.google.co.id/url?sa=t&rct=j&q=&esrc=s&source=web&cd=3&cad=rja&uact=8&ved=0ahUKEwj7u8nykb3TAhUCa7wKHUYZBYcQFggsMAI&url=https%3A%2F%2Fen.wikipedia.org%2Fwiki%2FKruskal%2527s_algorithm&usg=AFQjCNFRRZYfMjMX2s_2V_zHPI03tmnP4A&sig2=NXH3jqAsJtBiHfGz1zL3vQ)
	
    Kruskal’s algorithm is a method for producing a minimal spanning tree from a weighted graph. The algorithm I’ll cover here is actually a randomized version of Kruskal’s; the original works something like this:
    1. Throw all of the edges in the graph into a big burlap sack. (Or, you know, a set or something.)
    2. Pull out the edge with the lowest weight. If the edge connects two disjoint trees, join the trees. Otherwise, throw that edge away.
    3. Repeat until there are no more edges left.
[Learn More Here](http://weblog.jamisbuck.org/2011/1/3/maze-generation-kruskal-s-algorithm)


- Maze Feature
    1. Move Player --> Easily Moves The Player By Using The Keyboard Keys W A S D
    2. Generate New Random Layout --> New Layout Can Change Random Or Dynamic By Pressing The C Keyboard
 
### - Build & Run 
- **Windows**  
To Run This Program In Windows You Can Use The Codeblock Ideas ([Get Here](https://www.google.co.id/url?sa=t&rct=j&q=&esrc=s&source=web&cd=1&cad=rja&uact=8&ved=0ahUKEwjIp8ONmr3TAhVBNpQKHQfJDUQQFggkMAA&url=http%3A%2F%2Fwww.codeblocks.org%2Fdownloads&usg=AFQjCNGin5_gzph-iFTEZ-NsXkpwypBBNQ&sig2=L7-9vYIUSTwdC01iQdkVJQ)) After That Follow The Instructions The Installation With The Addition Of The Opengl Api ([Learn Here](http://www.sci.brooklyn.cuny.edu/~goetz/codeblocks/glut/)).  
_How To :_  
_**Create A New Project Glut/Opengl Project After That Just Copy Paste The Code In Your main.Cpp Has Been Made. Build & Run**_ 

- Linux  
1.You Can Use The Codeblock For Linux As Well.  
2.You Can Execute Your Code Using A Text Editor That You Love. Like Atoms, Sublime,Geany Or Another.  

  Before Executing, You Must Install Some Dependenci Of Glut On Linux. What You Need To Do Is (Installation Via Terminal):  
1.Install The Compiler And Necessary Tools.A Fairly Complete Compiler You Can Use G ++, Install: **sudo apt-get install g++ cmake**    
2.Install Freeglut : Install: **sudo apt-get install freeglut3 freeglut3-dev**  
3.Run Using Terminal : **gcc -o excecutebin filename.cpp -lglut -lGL -lm -lGLU -lstdc++**



### - Documentation  
**-V-1.0**  
1.In This Version, The Object The Player Can Still Penetrate The Wall  
2.Object Player Running (Right, Left, Bottom, Top) With Magnitude 0.1.  
3.The Shape Of The Maze Randomed By Using Button C & Player Can Walk A = Left, S = Down, D = To, W = Up  
4.Still 2 Dimensional Maze Form




