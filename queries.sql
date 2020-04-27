SELECT * FROM item_base WHERE id IN ( SELECT base_id FROM item_instance WHERE id = {};
