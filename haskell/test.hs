
double :: Num a => a -> a
double x = x + x

quad :: Num a => a -> a
quad x = double (double x)

second :: [a] -> a
second xs = head (tail xs)
swap :: (b, a) -> (a, b)
swap (x,y) = (y,x)
pair :: a -> b -> (a, b)
pair x y = (x,y)
palindrome :: Eq a => [a] -> Bool
palindrome xs = reverse xs == xs
twice :: (t -> t) -> t -> t
twice f x = f (f x)

(|||) :: Bool->Bool->Bool
False ||| False = False
_     ||| _     = True

numChar :: Char->String->Int
numChar x xs = length [x' | x' <- xs, x' == x]


scalarProduct:: [Int]->[Int]->Int
scalarProduct xs ys = sum [x*y | (x, y) <- zip xs ys]

split:: String->Char->[String]
split xs x = if x `elem` xs then takeWhile(/=x) xs : split (tail(dropWhile(/=x) xs)) x else [xs]

maxLoc:: [Int] -> [Int]
maxLoc xs = [b | ((a, b), c) <- zip (zip xs (tail xs)) (tail (tail xs)), b > a, b > c]

uoc:: Int -> [Int]
uoc n = [x | x <- [1..n], n `mod` x == 0, x < n]

perfect:: Int -> [Int]
perfect n = [x | x <-[1..n], sum (uoc x) == x]

andd:: [Bool]->Bool
andd [] = True
andd (x:xs) = if x then andd xs else False 

concatt:: [[a]] -> [a]
concatt [] = []
concatt [[xs]] = [xs]
concatt xs = head xs ++ concatt (tail xs)

replica :: Int->a->[a]
replica 0 a = []
replica n a = a : replica (n-1) a

mod3:: Int->Bool
mod3 n = n `mod` 3 == 0

merge :: Ord a => [a] -> [a] -> [a]
merge xs [] = xs
merge [] ys = ys
merge (x:xs) (y:ys) | x <= y    = x:merge xs (y:ys)
                    | otherwise = y:merge (x:xs) ys

msort :: Ord a => [a] -> [a]
msort [] = []
msort [xs] = [xs]
msort xs = merge (msort (take (div (length xs) 2) xs)) (msort (drop (div (length xs) 2) xs))

quicksort:: Ord a => [a] -> [a]
quicksort [] = []
quicksort (x:xs) = 
    quicksort smaller ++ [x] ++ quicksort larger
    where 
        smaller = [a | a <- xs, a <= x]
        larger = [b | b <- xs, b > x]

    
m :: Ord a => [a] -> [a] -> [a]
m xs [] = xs
m [] xs = xs
m (x:xs) (y:ys) = if x <= y then x : m xs (y:ys)
                            else y : m (x:xs) ys

ms :: Ord a => [a] -> [a]
ms [] = []
ms [x] = [x]
ms xs = m (ms (take (div (length xs) 2) xs)) (ms (drop (div (length xs) 2) xs))

data A = Y | N | U
x :: [A]
x = [Y, N , U, U]







qs :: Ord a => [a] -> [a]
qs [] = []
qs (x:xs) = qs smaller ++ [x] ++ qs larger
            where 
                smaller = [a | a <- xs, a <= x]
                larger = [a | a <- xs, a > x]    

checkpyth :: (Int, Int, Int) -> Bool
checkpyth (a,b,c) = c^2 == a^2 + b^2

pyths :: Int -> [(Int, Int, Int)]
pyths n = [(a,b,c) | a <- [1..n], b <- [1..n], c <- [1..n], checkpyth (a,b,c)]

square :: Int -> Bool
square x = length [y | y <-[1..x], y^2 == x] == 1

act :: IO (Char,Char)
act = do    x <- getChar
            getChar
            y <- getChar
            return (x,y)

tb :: [Int] -> (Float, Float)
tb l = (a,b) where  a = (sum l) / (length l)
                    b = product l ** div 1.0 length l

