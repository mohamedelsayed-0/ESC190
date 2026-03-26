def can_segment(s, word_dict):
    if s == "": 
        return True

    for word in word_dict:
        if len(word) > len(s): 
            continue

        if s[:len(word)] == word:
            if can_segment(s[len(word):], word_dict):
                return True

    return False

print(can_segment("catsandog", ["cats", "dog", "sand", "and", "cat"]))
print(can_segment("applepenapple", ["apple", "pen"]))
