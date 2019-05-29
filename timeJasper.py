import random
import re

WORDS = ["TIME"]

def handle(text, mic, profile):
    user_tz = getTimezone(profile)
    now = datetime.datetime.now(tz=user_tz)
    response = now.strftime("%I:%M %p")
    mic.say("It is %s right now." % (response))

def isValid(text):
    return bool(re.search(r'\btime\b', text, re.IGNORECASE))
