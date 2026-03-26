def f(x):
    return x ** 5 - 7 * x ** 4 + 13 * x ** 3 + 5 * x ** 2 - 48 * x + 20

def f_prime(x):
    return 5 * x ** 4 - 28 * x ** 3 + 39 * x ** 2 + 10 * x - 48

def gradient_descent(initial_guess, learning_rate=0.001, max_iter=100000):
    guess = initial_guess
    i = 0
    while f_prime(guess) > 10 ** -6 and i < max_iter:
        guess = guess - learning_rate * f_prime(guess)
        i += 1

    return guess

print(gradient_descent(5))
