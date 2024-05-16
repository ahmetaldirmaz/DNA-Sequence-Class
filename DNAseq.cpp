//
// Created by Ahmet Aldirmaz  on 15.04.2024.
//
// debugs:

// debug 1
// in constructor instead of directly assigning the private data
// members, first tried to create a new object and assign the private data members of the new object

//debug 2
// in the two-case addition operator, after searching for the first occurrence
// of the first nucleotide of rhs in sequence, forgot to check if the first nucleotide of rhs is found
// didn't add the firstNucOcc == false condition in the for loop at first
// you need that to stop updating the idx after the first occurrence is found
// since you use the idx to find the correct index to add the rhs sequence

#include "DNAseq.h"
#include <iostream>
#include <string>

using namespace std;

DNAseq::DNAseq() {  //default constructor

        length = 0;
        sequence = NULL;

}

DNAseq::DNAseq( const string & str_sequence ) { //parametric constructor


    if (str_sequence == "") { //if the string is empty

        length = 0;
        sequence = NULL;

    } else { //if the string is not empty

        length = str_sequence.length();
        sequence = new Nucleotide[length];

        if (sequence != NULL) {

            for (int i = 0; i < length; i++) {

                if (str_sequence[i] == 'A') {

                    sequence[i] = A;

                } else if (str_sequence[i] == 'C') {

                    sequence[i] = C;

                } else if (str_sequence[i] == 'G') {

                    sequence[i] = G;

                } else if (str_sequence[i] == 'T') {

                    sequence[i] = T;

                }

            }

        }


    }

}

DNAseq::DNAseq(const DNAseq & copyseq) { //copy constructor

    DNAseq seq;

    seq.length = copyseq.length;
    seq.sequence = new Nucleotide[seq.length];

    if (seq.sequence != NULL) {

        for (int i = 0; i < seq.length; i++) {

            seq.sequence[i] = copyseq.sequence[i];

        }

    }
}

DNAseq::~DNAseq() {

    delete[] sequence; //destructor

}

DNAseq &DNAseq::operator=(const DNAseq & rhs) {

    if ( this != & rhs ) { //if the object is not the same with rhs

        delete[] sequence;

        length = rhs.length;
        sequence = new Nucleotide[rhs.length];

        if (sequence != NULL) {

            for (int i = 0; i < length; i++) {

                sequence[i] = rhs.sequence[i];

            }

        }

    }

    return *this;
}

DNAseq DNAseq::operator+(const DNAseq & rhs) const {

    DNAseq newSeq;

    newSeq.length = length + rhs.length;
    newSeq.sequence = new Nucleotide[newSeq.length];

    bool firstNucOcc = false;
    int idx = 0;

    if (sequence != NULL && rhs.sequence != NULL){

        for (int i = 0; i < length && firstNucOcc == false; i++) {

            //find the first occurrence of the first nucleotide of rhs in sequence
            // stop when the first occurrence is found

            if (sequence[i] == rhs.sequence[0]) {

                firstNucOcc = true;
                idx = i;

            }

        }

    }
    if (firstNucOcc) { //if the first nucleotide of rhs is found

        for (int i = 0; i <= idx; i++) {

            newSeq.sequence[i] = sequence[i];

        }

        for (int i = 0; i < rhs.length; i++) {

            newSeq.sequence[idx + 1 + i] = rhs.sequence[i];

        }

        for (int i = 0; i < length - idx - 1; i++) {

            newSeq.sequence[idx + rhs.length + 1 + i] = sequence[idx + 1 + i];

        }

    } else { //if the first nucleotide of rhs is not found

        if(sequence != NULL) {

            for (int i = 0; i < length; i++) {

                newSeq.sequence[i] = sequence[i];

            }
        }
        if(rhs.sequence != NULL) {

            for (int i = 0; i < rhs.length; i++) {

                newSeq.sequence[length + i] = rhs.sequence[i];

            }
        }
    }

    return newSeq;

}


DNAseq DNAseq::operator - (const DNAseq & rhs) const {


    bool occurrence = false; // if rhs is found in sequence
    int occIdx = 0; // index of the first occurrence
    int lenCount = 0; // count of the length of the sequence

    if (sequence != NULL && rhs.sequence != NULL) {

        for (int i = 0; i < length && occurrence == false; i++) {

            if (sequence[i] == rhs.sequence[0]) { // if the first nucleotide of rhs is found

                occIdx = i; // index of the first occurrence updated
                occurrence = true;

                for ( int j = 0; j < rhs.length && i + j < length && occurrence == true; j++ ) {

                    if (sequence[i + j] == rhs.sequence[j]) { // while the latter nucleotides of rhs are same

                        lenCount++;

                    }
                    else {
                        occurrence = false; // if the sequence is not found
                        lenCount = 0;   // count is reset
                    }

                }

            }
            if ( lenCount != rhs.length ) {  // if the length of the sequence is not equal to rhs length
                occurrence = false; // the sequence is not found
            }

        }

    }

    DNAseq newSeq;

    if (occurrence) {

        newSeq.length = length - rhs.length;
        newSeq.sequence = new Nucleotide[newSeq.length];

        for (int i = 0; i < occIdx; i++) {

            newSeq.sequence[i] = sequence[i];

        }

        for (int i = 0; i < length - occIdx - rhs.length; i++) {

            newSeq.sequence[occIdx + i] = sequence[occIdx + rhs.length + i];

        }

    } else {

        newSeq.length = length;
        newSeq.sequence = new Nucleotide[newSeq.length];

        for (int i = 0; i < length; i++) {

            newSeq.sequence[i] = sequence[i];

        }

    }

    return newSeq;

}
DNAseq DNAseq::operator * ( int n ) const {

    DNAseq newSeq;

    newSeq.length = length * n; // new length is the length of the sequence times n
    newSeq.sequence = new Nucleotide[newSeq.length];

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < length; j++) {

            if (sequence[j] == A) {

                newSeq.sequence[i * length + j] = A;
                // finding the correct index for the new sequence
                // like it is a matrix

            } else if (sequence[j] == C) {

                newSeq.sequence[i * length + j] = C;

            } else if (sequence[j] == G) {

                newSeq.sequence[i * length + j] = G;

            } else if (sequence[j] == T) {

                newSeq.sequence[i * length + j] = T;

            }

        }

    }

    return newSeq;

}

DNAseq & DNAseq::operator += (const DNAseq & rhs) {

    *this = *this + rhs;
    // using the + and = operator to add the rhs to the lhs

    return *this;

}

DNAseq DNAseq::operator!() const {

    //complementing the sequence

    DNAseq newSeq;

    newSeq.length = length;
    newSeq.sequence = new Nucleotide[length];

    for (int i = 0; i < length; i++) {

        if (sequence[i] == A) {

            newSeq.sequence[i] = T;

        } else if (sequence[i] == C) {

            newSeq.sequence[i] = G;

        } else if (sequence[i] == G) {

            newSeq.sequence[i] = C;

        } else if (sequence[i] == T) {

            newSeq.sequence[i] = A;

        }

    }

    return newSeq;

}

string DNAseq::str_sequence() const {

    string seq = "";

    for (int i = 0; i < length; i++) {

        if (sequence[i] == A) {

            seq += "A";

        } else if (sequence[i] == C) {

            seq += "C";

        } else if (sequence[i] == G) {

            seq += "G";

        } else if (sequence[i] == T) {

            seq += "T";

        }

    }

    return seq;
}

Nucleotide * DNAseq::getSeq() const {

    return sequence;

}

int DNAseq::getLen() const {

    return length;

}

ostream & operator << (ostream & os, const DNAseq & rhs) {

        os << rhs.str_sequence();

        return os;

}

int operator % (const DNAseq & lhs, Nucleotide n) {

    int count = 0;

    for (int i = 0; i < lhs.getLen(); i++) {

        if (lhs.getSeq()[i] == n) {

            count++;

        }

    }

    return count;

}

bool operator <= (const DNAseq & lhs, const DNAseq & rhs) {

    bool isSub = false;
    int lenCount = 0;

    if (lhs.getSeq() != NULL && rhs.getSeq() != NULL) {

        if ( lhs.getLen() <= rhs.getLen() ) {

            for ( int i = 0; i < rhs.getLen() && isSub == false; i++ ) {

                if ( lhs.getSeq()[0] == rhs.getSeq()[i] ) {

                    isSub = true;

                    for ( int j = 0; j < lhs.getLen() && i+j < rhs.getLen() && isSub == true; j++ ) {

                        if ( lhs.getSeq()[j] == rhs.getSeq()[i+j] ) {

                            lenCount++;

                        }
                        else {

                            isSub = false;
                            lenCount = 0;
                        }


                    }

                }
                if (lenCount != lhs.getLen()) {

                    isSub = false;

                }

            }



        }

    }
    if (lhs.getSeq() == NULL && rhs.getSeq() == NULL) {

        isSub = true;

    }


    return isSub;

}


DNAseq operator + (Nucleotide lhs, const DNAseq & rhs) {


    string seq = rhs.str_sequence();

    if (lhs == A) {

        seq = "A" + seq;

    } else if (lhs == C) {

        seq = "C" + seq;

    } else if (lhs == G) {

        seq = "G" + seq;

    } else if (lhs == T) {

        seq = "T" + seq;

    }

    DNAseq newSeq(seq);

    return newSeq;

}