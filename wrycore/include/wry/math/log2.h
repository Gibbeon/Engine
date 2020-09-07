/*

template< unsigned int value_ > struct static_log2
{
    static const unsigned int result = static_log2< value_ / 2 >::result + 1 ;
};

template<> struct static_log2< 1 > { static const unsigned int result = 0 ; } ;
template<> struct static_log2< 0 > { } ;

*/