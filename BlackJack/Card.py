import random
import math
suits = {0:'\u2663',1:'\u2666',2:'\u2764',3:'\u2660'}
ranks = {0:'2', 1:'3', 2:'4', 3:'5', 4:'6', 5:'7', 6:'8', 7:'9', 8:'10', 9:'J', 10:'Q', 11:'K', 12:'A'}

def points(card_list):
    """Returns sum of all point values of cards in a list"""
    point_total = [ x.points() for x in card_list]
    result = math.fsum(point_total)
    return result
   
class Card:   
    def __init__(self, number):
        """Given an number between 0 and 50, creates an instance of a card"""
        if number >= 0 and number <= 51:
            self.number = number
        else:
            return "invalid number, number must be between 0 and 51"
        
    def __repr__(self):
        """Returns a string representation of a card rank and suit"""
        return str(ranks[self.rank()]) + '' + str(suits[self.suit()])
        
    def __lt__(self, other):
        """Returns True if card number is higher than other"""
        return self.number < other.number
    
    def rank(self):
        """Returns cards rank (i.e 'J',10,'A') when given card number"""
        return self.number%13
    
    def suit(self):
        """Returns card suit (i.e Unicode spade, heart, club, diamond)"""
        return self.number//13
    
    def points(self):
        """Returns card point value, 4 for Aces, 3 for King, 2 for Queen, 1 for Jack, and 0 for numbers"""
        r = self.rank()
        if r == 12:
            return 4
        if r == 11:
            return 3
        if r == 10:
            return 2
        if r == 9:
            return 1
        else:
            return 0
                
class BlackjackCard(Card):
    """subclass of Card, with different points for Blackjack game."""
    def points(self):
        """returns 11 for ace, 10 for other face cards, and a card's number value if not a face card"""
        r = self.rank()
        if r == 12:
            return 11
        if r == 11 or r == 10 or r==9:
            return 10
        else:
            return self.rank()+2
def total(hand):
    """Returns the total of a hand of cards in a Blackjack game"""
    result = 0
    numAces = 0
    for card in hand:
        result += card.points()
        if card.rank() == 12:
            numAces += 1
    while result > 21 and numAces > 0:
        result -= 10
        numAces -= 1
    return result
        
class Deck(list):
    """A list of cards"""
    def __init__(self):
        """Creates list of 52 cards"""
        for i in range(0,52):
            self.append(Card(i))
            
    def shuffle(self):
        """Returns shuffled deck of cards"""
        return random.shuffle(self)
    
    def deal(self,n):
        """Returns hand of n cards dealt from a deck"""
        n = int(n)
        hand = self[:n]
        del self[:n]
        return hand    
    
    def restore(self, a):
        """Returns deck with hand placed back in"""
        for card in a:
            self.append(card)


class PinochleDeck(Deck):
    """Deck of two sets of cards 9-A"""
    def __init__(self):
        for i in range(7,13):
            self.append(Card(i))
        for i in range(20,26):
            self.append(Card(i))
        for i in range(33,39):
            self.append(Card(i))
        for i in range(46,52):
            self.append(Card(i))
        self.extend(self)
        

    
        
    