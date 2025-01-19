from interlink_alg import interlink_alg

interlinks = ["A", "AB", "B", "BC", "C", "D", "CH", "E", "F", "EFG", "G", "FG", "H"]
identifiers = interlink_alg(interlinks)
print(identifiers)