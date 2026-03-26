# OPT(N) = min( OPT(n-d) + 1 )
#
def compute_opt(denoms, n):
    opt = [0] * (n + 1)

    for amount in range(1, n + 1):
        best = float('inf')

        for d in denoms:
            if d <= amount:
                best = min(best, opt[amount - d] + 1)

        opt[amount] = best

    return opt


def get_coins(denoms, n):
    opt = compute_opt(denoms, n)
    coins = []
    amount = n

    while amount > 0:
        for d in denoms:
            if d <= amount and opt[amount] == opt[amount - d] + 1:
                coins.append(d)
                amount -= d
                break

    return coins

print(get_coins([1, 4, 5], 8))
