
#ifndef VISCOELASTICFLUID_H
#define VISCOELASTICFLUID_H
class ViscoelasticFluid
{
  public :
    ViscoelasticFluid()=default;
    ~ViscoelasticFluid() noexcept =default;
    ViscoelasticFluid(const ViscoelasticFluid &)=default;
    ViscoelasticFluid & operator=(const ViscoelasticFluid &)=default;
    ViscoelasticFluid(ViscoelasticFluid &&)=default;
    ViscoelasticFluid & operator=(ViscoelasticFluid &&)=default;
};

#endif
