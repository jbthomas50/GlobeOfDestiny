import random
import re
import os

WORDS = ["WEATHER"]

def handle(text, mic, profile):
    messages = ["It is sunny outside.",
                "It is 70 degrees outside."]
    message = random.choice(messages)
    mic.say(message)

def isValid(text):
    return bool(re.search(r'\bweather\b', text, re.IGNORECASE))
