#!/usr/bin/env python3
'''
@author  Michele Tomaiuolo - http://www.ce.unipr.it/people/tomamic
@license This software is free - http://www.gnu.org/licenses/gpl.html
'''

def anagram(text: str) -> [str]:
    if len(text) == 0:
        return ['']

    result = []
    for i, char in enumerate(text):
        rest = text[:i] + text[i + 1:]
        for partial in anagram(rest):
            result.append(char + partial)
    return result

print(anagram("RAMO"))
