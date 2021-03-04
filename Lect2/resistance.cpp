//Дан следующий интерфейс, описывающий поведение материала в терминах "напряжение-деформация".

class Material
{
public:
    // Принимает на вход величину деформации.
    // Возвращает величину напряжения, посчитанную с учётом реологии материала.
    virtual float getStress(float strain) = 0;
};
//Реализуйте данный интерфейс для идеально-упругого материала и для упруго-пластического.

class ElasticMaterial : public Material
{
public:
    ElasticMaterial(float elasticModulus);
    float getStress(float strain) override;
private:
    float ElasticModulus;
};
class PlasticMaterial : public Material
{
public:
    PlasticMaterial(float elasticModulus, float strainLimit);
    float getStress(float strain) override;
private:
    float ElasticModulus;
    float StrainLimit;
};

ElasticMaterial::ElasticMaterial(float elasticModulus) : ElasticModulus(elasticModulus)
{ }
float ElasticMaterial::getStress(float strain)
{
    return strain * ElasticModulus;
}
PlasticMaterial::PlasticMaterial(float elasticModulus, float strainLimit) : ElasticModulus(elasticModulus), StrainLimit(strainLimit)
{}
float PlasticMaterial::getStress(float strain)
{
    if (strain > StrainLimit)
        return ElasticModulus * StrainLimit;
    
    return ElasticModulus * strain;
}
