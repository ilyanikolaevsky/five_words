# five_words
A solution to the problem of finding five English words with 25 distinct characters, using dynamic programming.

This is the problem Matt Parker brought up in his video https://www.youtube.com/watch?v=_-AfhLQfb6w

The solution uses dynamic programming to store if it's possible to construct every set of letters using 5-letter words.
After this information is computed and stored, it's used to bruteforece without any deadends.
