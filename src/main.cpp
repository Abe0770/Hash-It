            input = readFileContents(argv[3]);
        } else {
            printUsage(argv[0]);
            return 1;
        }

        hasher -> hashString(input);
        hasher -> display();

    } catch (const std::exception& e) {
        cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}