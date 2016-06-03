function [ mass ] = Mass( bruttoWeight, tankLevel, tankVolume )
    % bruttoWeight is the weight without fuel in tonnes
    % tankLevel is percentage of tankVolume filled (0.0-1.0)
    % tankVolume is the maximum weight of the filled tank in tonnes
    
    mass = bruttoWeight + tankLevel * tankVolume;
end

