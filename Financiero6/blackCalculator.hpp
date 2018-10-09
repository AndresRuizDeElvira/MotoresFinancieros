//
//  blackCalculator.hpp
//  
//
//  Created by Andres on 9/10/18.
//

#ifndef blackCalculator_hpp
#define blackCalculator_hpp

class BlackCalculator {
private:
    class Calculator;
    friend class Calculator;
public:
    BlackCalculator(const ext::shared_ptr<StrikedTypePayoff>& payoff,
                    Real forward,
                    Real stdDev,
                    Real discount = 1.0);
    BlackCalculator(Option::Type optionType,
                    Real strike,
                    Real forward,
                    Real stdDev,
                    Real discount = 1.0);
    virtual ~BlackCalculator() {}
    
    Real value() const;
    
    /*! Sensitivity to change in the underlying forward price. */
    Real deltaForward() const;
    /*! Sensitivity to change in the underlying spot price. */
    virtual Real delta(Real spot) const;
    
    /*! Sensitivity in percent to a percent change in the
     underlying forward price. */
    Real elasticityForward() const;
    /*! Sensitivity in percent to a percent change in the
     underlying spot price. */
    virtual Real elasticity(Real spot) const;
    
    /*! Second order derivative with respect to change in the
     underlying forward price. */
    Real gammaForward() const;
    /*! Second order derivative with respect to change in the
     underlying spot price. */
    virtual Real gamma(Real spot) const;
    
    /*! Sensitivity to time to maturity. */
    virtual Real theta(Real spot,
                       Time maturity) const;
    /*! Sensitivity to time to maturity per day,
     assuming 365 day per year. */
    virtual Real thetaPerDay(Real spot,
                             Time maturity) const;
    
    /*! Sensitivity to volatility. */
    Real vega(Time maturity) const;
    
    /*! Sensitivity to discounting rate. */
    Real rho(Time maturity) const;
    
    /*! Sensitivity to dividend/growth rate. */
    Real dividendRho(Time maturity) const;
    
    /*! Probability of being in the money in the bond martingale
     measure, i.e. N(d2).
     It is a risk-neutral probability, not the real world one.
     */
    Real itmCashProbability() const;
    
    /*! Probability of being in the money in the asset martingale
     measure, i.e. N(d1).
     It is a risk-neutral probability, not the real world one.
     */
    Real itmAssetProbability() const;
    
    /*! Sensitivity to strike. */
    Real strikeSensitivity() const;
    
    Real alpha() const;
    Real beta() const;
protected:
    void initialize(const ext::shared_ptr<StrikedTypePayoff>& p);
    Real strike_, forward_, stdDev_, discount_, variance_;
    Real d1_, d2_;
    Real alpha_, beta_, DalphaDd1_, DbetaDd2_;
    Real n_d1_, cum_d1_, n_d2_, cum_d2_;
    Real x_, DxDs_, DxDstrike_;
};

// inline
inline Real BlackCalculator::thetaPerDay(Real spot,
                                         Time maturity) const {
    return theta(spot, maturity)/365.0;
}

inline Real BlackCalculator::itmCashProbability() const {
    return cum_d2_;
}

inline Real BlackCalculator::itmAssetProbability() const {
    return cum_d1_;
}

inline Real BlackCalculator::alpha() const {
    return alpha_;
}

inline Real BlackCalculator::beta() const {
    return beta_;
}

}

#endif
