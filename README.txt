	The Knight’s tour is a challenge in which a single person has a knight

piece from a chess set and with that set, the must successfully move to each square 

on the chessboard without visiting the same square more than once. Theoretically,

no matter where the initial coordinate is of the knight, there is always at

least one path in which the knight can traverse through and successfully visit

every single coordinate on the chess board. There are several methods that the

player can use to successfully complete this challenge, however one of the more

famous methods, is by following the Warnsdoff’s rule. Warnsdoff’s rule states that

the next move should be chosen based upon which of the following possible moves

have the least number of available spots open. Whichever of all the following

possible moves that has the least number of options, should be selected as the 

next move. Using this rule, a player can theoretically complete this challenge no

matter what the initial conditions are. However, for this project, Warnsdoff rule

can only be used for the first 32 moves of the challenge. For the last 32 moves the 

choices must be made in an exhaustive manner.

	The second set of 32 moves requires a singly listed stack in which 

coordinates and other miscellaneous data must be implemented into each ‘node’ or 

move. Since this singly listed stack has a “first in last out” behavior back tracking 

must be used to find other possible combinations that can be used to complete the 

challenge. This type of algorithm that must be implemented is called a brute force 

method. 
