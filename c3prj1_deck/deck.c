#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deck.h"
#include "eval.h"
#include "cards.h"

void add_card_to(deck_t * deck, card_t c){
  //Add card to deck
  assert(deck != NULL);

  card_t * card = malloc(sizeof(*card));
  assert(card != NULL);

  card->value = c.value;
  card->suit = c.suit;
  
  deck->n_cards++;
  deck->cards = realloc(deck->cards,deck->n_cards*sizeof(deck->cards));
  deck->cards[deck->n_cards-1] = card;
}

card_t * add_empty_card(deck_t * deck){
  //Adds a card whose value and suit are both 0 and returns a pointer to it in the deck
  assert(deck != NULL);
  card_t * empty_card = malloc(sizeof(*empty_card));
  empty_card->value = 0;
  empty_card->suit = 0;
  add_card_to(deck,*empty_card);
  free(empty_card);
  return deck->cards[deck->n_cards-1];
}

deck_t * make_deck_exclude(deck_t * excluded_cards){
  deck_t * answer = malloc(sizeof(*answer));
  card_t card;
  answer->cards = NULL;
  answer ->n_cards = 0;

  for (int i=0;i<52;i++){
    card = card_from_num(i);
    if(!deck_contains(excluded_cards,card)){
      add_card_to(answer,card);
    }
  }
  return answer;
}

deck_t * build_remaining_deck(deck_t ** hands, size_t n_hands){
  //Create a temporary deck to hold the cards to be excluded
  deck_t temp;
  temp.cards = NULL;
  temp.n_cards = 0;

  //Loop through all hands passed in
  for(int i=0;i<n_hands;i++){
    //Loop through each card in the current hand
    for (int j=0;j<hands[i]->n_cards;j++){
      //If it is not an unknown hand
      if(!is_empty_card(hands[i]->cards[j])){
	//Add it to the temporary deck
	add_card_to(&temp, *hands[i]->cards[j]);
      }
    }
  }

  //Fill a full deck of cards not including all the cards in the temp dek
  deck_t * answer = make_deck_exclude(&temp);

  //Clean up and return
  free_cards(&temp);
  return answer;
}

void free_cards(deck_t * deck){
  for(int i=0;i<deck->n_cards;i++){
    free(deck->cards[i]);
  }
  free(deck->cards);
  deck->n_cards = 0;
  deck->cards = NULL;
}

void free_deck(deck_t * deck){
  free_cards(deck);
  free(deck);
}

  





	
  
  



void print_hand(deck_t * hand){
  for(int i=0;i<hand->n_cards;i++){
    print_card(*hand->cards[i]);
    printf(" ");
  }
}

int deck_contains(deck_t * d, card_t c) {
  for(int i=0;i<d->n_cards;i++){
    if (d->cards[i]->value ==  c.value && d->cards[i]->suit == c.suit){
      return 1;
    }
  }
  return 0;
}

//Helper function for shuffling decks
//Takes a deck and index of two cards and swaps them

void swap (deck_t * deck, int c1, int c2){
  card_t *temp = deck->cards[c1];
  deck->cards[c1] = deck->cards[c2];
  deck->cards[c2] = temp;
}
/*
void shuffle(deck_t * d){
  for(int i=0;i<d->n_cards;i++){
    int randInt = random() % d->n_cards;
    swap(d,i,randInt);
  }
}
*/

void shuffle(deck_t * d){
  card_t ** card =d -> cards ;
  card_t * temp;
  size_t n=d ->n_cards;
  int randarry;
  for (size_t i=0 ;i< n/2 ;i++){
    randarry= random()%(n-i)+i;
    temp=card[i];
    card[i]=card[randarry];
    card[randarry]=temp;
  }
}
void assert_full_deck(deck_t * d) {
  for(int i=0;i<52;i++){
    assert(deck_contains(d,card_from_num(i)));
  }
}
