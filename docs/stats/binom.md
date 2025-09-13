# The probability mass function of a binomial distribution
This function defines the probability that a discrete random variable is exactly equal to some value. For a binomial distribution, where we're interested in one of two choices, this function requires inputs *k*, *p* and *n*, and outputs the probability of observing the particular value of interest $k$ times if it has a probability *p* of happening and we run *n* experiments.

In a coin toss example, we're interested in knowing the probability of getting $k=2$ tails with a biased coin if we perform $n=3$ coin flips. There's a $70\%$ chance we get tails $(p=0.7)$ on each coin toss with this biased coin. So if we flip the coin three times, the probability mass function will tell us how likely it is to get tails two times.

First, we lay out all of the possible outcomes that *n=3* consecutive coin flips could result in: HHH, TTH, THH, and so on. If the coin were to be fair (*p=0.5*), then each of the $2^3=8$ resulting sequences would be equally likely and, say, the HTT sequence would have a probability of $0.5 \times 0.5 \times 0.5 = 0.125$ of happening. However, since our coin is biased, the HTT sequence has a probability of $0.3 \times 0.7 \times 0.7 = 0.3 \times 0.7^2 = 0.147$. As well, the sequence THT would have the same probability: $0.7 \times 0.3 \times 0.7 = 0.7^2 \times 0.3 = 0.147$, since there are two tails in both sequences. So sequences with the same number of tails have the **same probability**.

Now, let's visualize all 8 possible sequences for our 3 flips:

```
0 tails: HHH                    → probability = 0.3³ = 0.027
1 tail:  THH, HTH, HHT          → each has probability = 0.7¹ × 0.3² = 0.063
2 tails: TTH, THT, HTT          → each has probability = 0.7² × 0.3¹ = 0.147
3 tails: TTT                    → probability = 0.7³ = 0.343
```

There's one way to get zero tails, three ways to get one tail, three ways to get two tails, and one way to get three tails. These numbers ($1, 3, 3, 1$) aren't random, they come from asking “in how many ways can I choose positions for the tails?”. Now, mathematicians write this as $C(n, k)$ or “$n$ choose $k$” (sometimes also written as ${n \choose r}$ or ${}_nC_r$). For $n=3$ flips and $k=2$ tails, we know now that $C(3,2) = 3$, where $C(n,k) = \frac{n!}{k!(n-k)!}$. Again, this means that there are three different ways in which we could get two tails with three flips. The formula comes from thinking about choices: you have $n$ slots total, need to pick $k$ of them, and the order in which you pick them doesn't matter (THT and TTH are different sequences, but they're both “$2$ tails chosen from $3$ positions”).

At the same time, we've noticed there's a pattern: for any sequence with exactly $k$ tails and $n-k$ heads, we:
- Multiplied $p$ exactly $k$ times by itself (for $k=2$ tails: $0.7 \times 0.7 = 0.7^2$)
- Multiplied $1-p$ exactly $n-k$ times by itself (for $k=2$, $1-0.7=0.3$, $n-k=3-2=1$, therefore, $0.3^1=0.3$)

And the order didn't matter for multiplication, since multiplication is commutative. Now, lastly, if we put these two pieces together, we can calculate now how likely it is to get exactly $k$ tails on $n$ coin flips:

1. **We count the arrangements**: There are $C(n,k)$ different sequences with exactly $k$ tails
2. **We calculate the probability per sequence**: Each sequence has probability $p^k \times (1-p)^{n-k}$

Since we're adding the same probability $C(n,k)$ times, we can multiply them:

$$P(X = k) = C(n,k) \times p^k \times (1-p)^{n-k}$$

For instance, the probability to get exactly 2 tails in our 3 flips with $p=0.7$ is:
$P(X = 2) = C(3,2) \times 0.7^2 \times 0.3^1$
$P(X = 2) = 3 \times 0.49 \times 0.3$
$P(X = 2) = 0.441$

This means there's a 44.1% chance of getting exactly 2 tails in 3 flips of our biased coin. And this is what the probability mass function tells us. If we calculate this for all possible values of $k$ (from 0 to $n$), the PMF gives us the complete probability distribution: we can see which outcomes are most likely and by how much. In our example, getting 3 tails (34.3%) is most likely, while getting 0 tails (2.7%) is least likely, exactly as we'd expect from a coin biased toward tails.

# Cumulative distribution function
Now, intuitively, if we're interested in knowing how likely it is that we get less than two tails, we would sum the probability of getting exactly zero tails plus the probability of getting exactly one tail, so $0.027 + 0.063 = 0.090$. And that's what the cumulative function does. Now, for instance, if I were to perform five coin tosses, to estimate the probability of getting two or more tails and four or fewer tails, we would do cdf(k=4, n=5, p=0.5) - cdf(k=1, n=5, p=0.5).