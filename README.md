# guild-contract-fullfillment-engine
Mock DSA Test 5

Context

You’ve been hired as a backend engineer by the Craftwright's Guild, 
a decentralized medieval supply chain where blacksmiths, alchemists, 
and jewelers post contracts to request specific items in exchange for payment.

Each contract lists:

    The final item the customer wants (e.g., IronSword)
    A list of recipes for crafting items (e.g., to make an IronSword, you might need IronIngot and WoodHandle)
    A current inventory of raw materials the player has

A contract must be fulfilled in full. 
If you can't produce the requested item, you return a ContractFailure object 
showing which sub-item(s) were missing or blocked. 
If you can fulfill it, you must deduct all used materials from the inventory and return success.

Some recipes are nested (e.g., to make a WoodHandle, you first need Plank, which is made from WoodLog).
