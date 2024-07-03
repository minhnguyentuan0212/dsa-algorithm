import Prelude

factors :: Int -> [Int]
factors n = [x | x <- [1..(n - 1)], n `mod` x == 0]


countPerfect :: [Int] -> Int
countPerfect [] = 0
countPerfect (x:xs) | sum (factors x) == x && (x /= 0) = 1 + countPerfect xs
                    | otherwise = countPerfect xs

scalarProduct :: [Int] -> [Int] -> Int
scalarProduct xs ys = sum [x * y | (x, y) <- zip xs ys]

--Caesar cipher only alphabet strings
caesarCipher :: [Char] -> Int -> [Char]
caesarCipher [] _ = []
caesarCipher (x:xs) n | x == ' ' = ' ' : caesarCipher xs n
                       | x == 'z' = 'a' : caesarCipher xs n
                       | x == 'Z' = 'A' : caesarCipher xs n
                       | otherwise = toEnum (fromEnum x + n) : caesarCipher xs n

isPalindrome :: [Int] -> Bool
isPalindrome xs = xs == reverse xs

scytale :: [Char] -> [Char]
-- Number of columns is 5
scytale xs = [xs !! i | i <- [0, 5..length xs - 1]] ++ [xs !! i | i <- [1, 6..length xs - 1]] ++ [xs !! i | i <- [2, 7..length xs - 1]] ++ [xs !! i | i <- [3, 8..length xs - 1]] ++ [xs !! i | i <- [4, 9..length xs - 1]]

