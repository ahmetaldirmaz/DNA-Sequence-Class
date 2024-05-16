//
// Created by Ahmet Aldirmaz  on 15.04.2024.
//

#ifndef HOMEW4_DNASEQ_H
#define HOMEW4_DNASEQ_H

#include <iostream>
#include <string>

using namespace std;

enum Nucleotide {A, C, G, T};


class DNAseq {

private:

    int length;
    Nucleotide * sequence;

public:

    DNAseq();
    DNAseq( const string & sequence );
    DNAseq ( const DNAseq & copyseq );
    ~DNAseq();

    string str_sequence() const; //return the DNA sequence as a string

    Nucleotide * getSeq() const; //return the DNA sequence as a Nucleotide array

    int getLen() const; //return the length of the DNA sequence

    DNAseq & operator = ( const DNAseq & rhs );

    DNAseq & operator += ( const DNAseq & rhs );

    DNAseq operator + (const DNAseq & rhs) const;

    DNAseq operator - (const DNAseq & rhs) const;

    DNAseq operator * ( int n ) const;

    DNAseq operator ! () const;

};

ostream & operator << (ostream & os, const DNAseq & dna);

int operator % (const DNAseq & lhs, Nucleotide n);

bool operator <= (const DNAseq & lhs, const DNAseq & rhs);

DNAseq operator + (Nucleotide lhs, const DNAseq & rhs);






#endif //HOMEW4_DNASEQ_H
