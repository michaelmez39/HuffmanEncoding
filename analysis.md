## Huffman Encoding Analysis and Reflection

### Computational Complexity
#### Overview
|Operation|Time Complexity|
|---|---|
|Construction| O(nlogn) |
|Get Character Code| O(logn) |
|Encode| O(n)/O(nlogm) |
|Decode| O(n) |

#### Huffman Tree Construction
To construct the Huffman tree, the algorithm has to go through these three steps: getting the frequency of each letter, putting the letters into a priority queue, and merging them into a tree. Finding the frequency of each letter in the file is achieved in O(n) time, where n is the length of the file. Putting all of them into a priority queue takes O(nlogn) time, and merging them into the completed Huffman tree takes O(nlogn) time, because we have go through every node, O(n), and reset the priority queue O(logn). This gives an overall time complexity of O(nlogn).

#### Get Character Code Operation
Getting the character code takes O(logn) time, where n is the number of unique characters in the file. To get the character code, we have to traverse the Huffman tree. This could be achieved in O(n) time with a hash table, but in most cases n will be small.

#### Encode
To encode the file, we need to go through all characters n, and find the character with get character, taking O(logm) with m being the number of different characters. This operation takes in total O(nlogm) time. If n is much larger than m, which is fairly common, the time complexity would appear to be O(n).

#### Decode
For decoding the file, we need to keep a pointer in the Huffman tree, and for every character in the file, move the pointer through the tree. When a leaf is reached in the tree, we find the decoded character. We only need to go through this once, this has a time complexity of O(n).

### Hardest Part
To look at the hard part I'll look at roughly how long each part takes, and how I felt during that part of the project.

#### Productive Main Write Through
For this project, I wrote the main bulk of the code in two or three sittings. A lot of times I will write some and than test, but this time I was impatient and just wrote everything and ran the tests.

#### First Round Debugging to Compile
For the first round there were a few segaults that popped up, but I was able to fix those fairly quickly. This process was mainly driven by getting the code to not have compilation and runtime errors. After it started to run, it seemed like it wasn't outputting any strings. This took a while to figure out, but the problem was forgetting to append the decoded letter to the result of decoding.

#### Second Round Debugging aka Frustrating
After it started ouptputting strings, sadly all the test cases didn't start passing. Instead of beautifully decoded strings it printed out a bunch of weird question marks and random characters. Following this, I looked at the slides on Huffman coding and did an in depth review of all the code. Some errors that I caught after going through this process were that I had accidently used a max heap instead of a min heap, this only took a few minutes to fix. With a fixed priority queue, I hoped the random character problem would get better, and it did. Now the strings were printing all the correct characters, with a bunch of random stuff in between. This was worrying because I knew it meant that somewhere along the line the strings were not being terminated correctly. Going back through all the code, I finally found the spot after writing functions to see what each character was encoded as and view the contents of the complete Huffman Tree. I had cast a single char to a string with `std::string(&char)`, in a heap allocated binary tree node. This is problematic because this made a regular char look like a c-string, which is null terminated. Because that char wasn't null terminated, it made strings out of random heap memory until it reached a null character.


### What I Learned
Because I was fairly confident that I was writing everything correctly in my code while I was writing it, I didn't take time to check every individual component of the project before moving on to the next (other than what is checked by my ide). This assumption wasn't completely misplaced because looking back, I didn't really have a lot of mistakes. Even though I did a good job the first write through, the mistakes that I did have took much longer to find because I had to go through every piece of the algorithm with every mistake, and in the end I wrote all the tests that I didn't want to write in the first place, and more. The main lesson is that even if I think I'm a perfect programmer, it's much easier to find mistakes early in a little piece of code than find mistakes later in a huge piece of code.
